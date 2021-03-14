#include "characterdatasource.h"

#include "database/databasemanager.h"

#include <QBuffer>
#include <QMap>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QSqlRecord>
#include <QStack>
#include <QTextDocument>
#include <QUrl>
#include <QUrlQuery>

CharacterDataSource::CharacterDataSource()
{
}

void CharacterDataSource::insertCharacter(const Character character)
{
    DatabaseManager::getInsetance().query(R"(INSERT INTO "character"("name","server","level","exp","popularity","job","job_detail","guild","avatar","avatar_url") VALUES(:name, :server, :level, :exp, :popularity, :job, :job_detail, :guild, :avatar, :avatar_url))", this->getCharacterBindValues(character));
}

Character CharacterDataSource::getCharacter(const QString name)
{
    QMap<QString, QVariant> bindValues{{":name", name}};
    QSqlQuery query = DatabaseManager::getInsetance().query(R"(SELECT * FROM "character" WHERE name = :name)", bindValues);
    if(query.first()) {
        qDebug()<<"character found";
        return Character(query);
    }
    return Character::getNoDataCharacter();
}

Character CharacterDataSource::getCharacterFromWeb(const QString name)
{
    QUrl url("https://maplestory.nexon.com/Ranking/World/Total");
    QUrlQuery query;
    query.addQueryItem("c", name);
    url.setQuery(query);
    QNetworkRequest request(url);
    return this->parseCharacterFromWeb(this->requests.get(request));
}

QList<Character> CharacterDataSource::getAllCharacters()
{
    QSqlQuery query = DatabaseManager::getInsetance().query(R"(SELECT * FROM "main"."character")");
    QList<Character> characterList;
    while(query.next()) {
        characterList.append(Character(query));
    }
    return characterList;
}

void CharacterDataSource::updateCharacter(const QString name, const Character character)
{
    QMap<QString, QVariant> bindValues = this->getCharacterBindValues(character);
    bindValues.insert(":targetName", name);
    DatabaseManager::getInsetance().query(R"(UPDATE "character" SET ("name","server","level","exp","popularity","job","job_detail","guild","avatar","avatar_url") VALUES(:name, :server, :level, :exp, :popularity, :job, :job_detail, :guild, :avatar, :avatar_url) WHERE name= :targetName)");
}

void CharacterDataSource::removeCharacter(const QString name)
{
    QMap<QString, QVariant> bindValues{{":name", name}};
    DatabaseManager::getInsetance().query(R"(DELETE FROM "character" WHERE name = :name)", bindValues);
}

const QMap<QString, QVariant> CharacterDataSource::getCharacterBindValues(Character character)
{
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    character.getAvatar().save(&buffer, "png");
    return QMap<QString, QVariant> {
        {":name", character.getName()},
        {":server", character.getServer()},
        {":level", character.getLevel()},
        {":exp", character.getExp()},
        {":popularity", character.getPopularity()},
        {":job", character.getJob()},
        {":job_detail", character.getJobDetail()},
        {":guild", character.getGuild()},
        {":avatar", bArray},
        {":avatar_url", character.getAvatarUrl()},
    };
}

const Character CharacterDataSource::parseCharacterFromWeb(QNetworkReply *reply)
{
    QString resultString = reply->readAll();

    if(this->serverIndexMap.empty()) {
        int worldIndex = resultString.indexOf(R"(<th>월드</th>)");
        if(worldIndex > 0) {
            QString targetString = resultString.mid(worldIndex);
            targetString = targetString.left(targetString.indexOf(R"(</td>)"));
            QStringList targetStringList = targetString.split(QRegularExpression(R"((\r)?\n)"));
            QRegularExpression serverExpression(R"server(.*?<img src="https://ssl.nx.com/s2/game/maplestory/renewal/common/world_icon/icon_(?<index>\d+)\.png" alt="(?<name>.*?)" />.*)server");
            for(auto targetLine: targetStringList) {
                QRegularExpressionMatch match = serverExpression.match(targetLine);
                if(match.isValid()) {
                    this->serverIndexMap.insert(match.captured("index").toInt(), match.captured("name"));
                }
            }
            qDebug()<<"serverIndexMap"<<serverIndexMap;
        }
    }

    int searchComChkIndex = resultString.indexOf(R"(<tr class="search_com_chk">)");
    if(searchComChkIndex > 0) {
        QString targetString = resultString.mid(searchComChkIndex);
        targetString = targetString.left(targetString.indexOf(R"(</tr>)") + 5);
        QStringList tdList;
        int targetIndex = 0;
        while(true) {
            int start = targetString.indexOf(R"(<td)", targetIndex);
            int end = targetString.indexOf(R"(</td>)", targetIndex);
            if(start == -1 || end == -1) break;
            tdList.append(targetString.mid(start, end + 5 - start));
            targetIndex = end + 1;
        }
        QString name, server, job, jobDetail, guild, avatarUrl;
        int level, exp, popularity;
        QRegularExpression leftExpression(R"left((?:.|\n)*?<img class="" src="(?<avatar_url>.*?)" (?:.|\n)*?world_icon/icon_(?<server>\d+)\.png" (?:.|\n)*?>(?<name>.*?)</a></dt>(:?.|\n)*?<dd>(?<job>.*?) / (?<job_detail>.*?)</dd>(?:.|\n)*)left");
        QRegularExpressionMatch match = leftExpression.match(tdList.at(1));
        if(match.isValid()) {
            name = match.captured("name");
            server = this->serverIndexMap[match.captured("server").toInt()];
            job = match.captured("job");
            jobDetail = match.captured("job_detail");
            avatarUrl = match.captured("avatar_url");
        }
        QRegularExpression levelExpression(R"(<td>Lv.(?<level>\d+)</td>)");
        match = levelExpression.match(tdList.at(2));
        if(match.isValid()) {
            level = match.captured("level").toInt();
        }

        QRegularExpression tdExpression(R"(<td>(.*?)</td>)");
        match = tdExpression.match(tdList.at(3));
        if(match.isValid()) {
            exp = match.captured(1).remove(',').toULongLong();
        }
        match = tdExpression.match(tdList.at(4));
        if(match.isValid()) {
            popularity = match.captured(1).remove(',').toInt();
        }
        match = tdExpression.match(tdList.at(5));
        if(match.isValid()) {
            guild = match.captured(1);
        }
        return Character(name, server, level, exp, popularity, job, jobDetail, guild, this->getAvatarImage(avatarUrl), avatarUrl);
    }
    return Character::getNoDataCharacter();
}

const QPixmap CharacterDataSource::getAvatarImage(QString avatarUrl)
{
    QNetworkReply *reply = this->requests.get(QNetworkRequest(QUrl(avatarUrl)));
    QPixmap avatarPixmap;
    avatarPixmap.loadFromData(reply->readAll(), "png");
    return avatarPixmap;
}
