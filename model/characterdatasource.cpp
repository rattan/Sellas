#include "characterdatasource.h"

#include "database/databasemanager.h"

#include <QMap>

CharacterDataSource::CharacterDataSource()
{
}

void CharacterDataSource::insertCharacter(const Character character)
{
    DatabaseManager::getInsetance().query(R"(INSERT INTO "character"("name","server","level","exp","popularity","job","job_detail","guild","avatar_cache","avatar_web") VALUES(:name, :server, :level, :exp, :popularity, :job, :job_detaail, :guild, :avatar_cache, :avatar_web))", this->getCharacterBindValues(character));
}

Character CharacterDataSource::getCharacter(const QString name)
{
    QMap<QString, QVariant> bindValues{{":name", name}};
    QSqlQuery query = DatabaseManager::getInsetance().query(R"(SELECT * FROM "character" WHERE name = :name)", bindValues);
    if(query.first()) {
        qDebug()<<"character found";
        return Character(query);
    }
    return Character("","",0,0,0,"","","","","");
}

QList<Character> CharacterDataSource::getAllCharacters()
{
    QSqlQuery query = DatabaseManager::getInsetance().query(R"(SELECT * FROM "character")");
    QList<Character> characterList;
    if(query.next()) {
        characterList.append(Character(query));
    }
    return characterList;
}

void CharacterDataSource::updateCharacter(const QString name, const Character character)
{
    QMap<QString, QVariant> bindValues = this->getCharacterBindValues(character);
    bindValues.insert(":targetName", name);
    DatabaseManager::getInsetance().query(R"(UPDATE "character" SET ("name","server","level","exp","popularity","job","job_detail","guild","avatar_cache","avatar_web") VALUES(:name, :server, :level, :exp, :popularity, :job, :job_detaail, :guild, :avatar_cache, :avatar_web) WHERE name= :targetName)");
}

void CharacterDataSource::removeCharacter(const QString name)
{
    QMap<QString, QVariant> bindValues{{":name", name}};
    DatabaseManager::getInsetance().query(R"(DELETE FROM "character" WHERE name = :name)", bindValues);
}

const QMap<QString, QVariant> CharacterDataSource::getCharacterBindValues(Character character)
{
    return QMap<QString, QVariant> {
        {":name", character.getName()},
        {":server", character.getServer()},
        {":level", character.getLevel()},
        {":exp", character.getExp()},
        {":popularity", character.getPopularity()},
        {":job", character.getJob()},
        {":job_detail", character.getJobDetail()},
        {":guild", character.getGuild()},
        {":avatar_cache", character.getAvatarCache()},
        {":avatar_web", character.getAvatarWeb()},
    };
}
