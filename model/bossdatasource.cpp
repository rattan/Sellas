#include "bossdatasource.h"

#include <database/databasemanager.h>

#include <QDateTime>
#include <QTime>

BossDataSource::BossDataSource()
{

}

void BossDataSource::insertBossesForCharacter(QString characterName, QList<Boss> bossList)
{
    for(auto boss: bossList) {
        this->insertBossForCharacter(characterName, boss);
    }
}

void BossDataSource::insertBossForCharacter(QString characterName, Boss boss)
{
    for(auto difficult: boss.getDifficultList()) {
        QMap<QString, QVariant> insertBindValue {
            {":character_name", characterName},
            {":name", boss.getName()},
            {":difficulty", difficult.getName()},
            {":clear_date", 0}
        };
        DatabaseManager::getInsetance().query(R"(INSERT INTO "boss"("character_name", "name", "difficulty", "clear_date") VALUES(:character_name, :name, :difficulty, :clear_date))", insertBindValue);
    }
}

void BossDataSource::clearBossNow(QString characterName, QString bossName, QString Difficulty)
{
    QMap<QString, QVariant> updateBindValue {
        {":character_name", characterName},
        {":name", bossName},
        {":difficulty", Difficulty},
        {":clear_date", QDateTime::currentDateTime().toSecsSinceEpoch()}
    };
    DatabaseManager::getInsetance().query(R"(UPDATE "boss" SET clear_date=:clear_date WHERE character_name=:character_name AND name=:name AND difficulty=:difficulty)", updateBindValue);
}

void BossDataSource::clearBossCancel(QString characterName, QString bossName, QString Difficulty)
{
    QMap<QString, QVariant> updateBindValue {
        {":character_name", characterName},
        {":name", bossName},
        {":difficulty", Difficulty},
        {":clear_date", 0}
    };
    DatabaseManager::getInsetance().query(R"(UPDATE "boss" SET clear_date=:clear_date WHERE character_name=:character_name AND name=:name AND difficulty=:difficulty)", updateBindValue);
}

Boss::Clear BossDataSource::getBossClear(QString characterName, QString bossName, QString Difficulty)
{
    return Boss::Clear("", "", 0);
}

QList<Boss::Clear> BossDataSource::getBossClear(QString characterName, QString bossName)
{
    QMap<QString, QVariant> updateBindValue {
        {":character_name", characterName},
        {":name", bossName}
    };
    QSqlQuery query = DatabaseManager::getInsetance().query(R"(SELECT * FROM "boss" WHERE character_name=:character_name AND name=:name)", updateBindValue);
    QList<Boss::Clear> bossClearData;
    while(query.next()) {
        bossClearData.append(Boss::Clear(query.value("name").toString(), query.value("difficulty").toString(), query.value("clear_date").toInt()));
    }
    return bossClearData;
}
