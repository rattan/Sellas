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
    qDebug()<<characterName;
    qDebug()<<bossName;
    qDebug()<<Difficulty;
    qDebug()<<QDateTime::currentDateTime().toSecsSinceEpoch();
    DatabaseManager::getInsetance().query(R"(UPDATE "boss" SET clear_date=:clear_date WHERE character_name=:character_name AND name=:name AND difficulty=:difficulty)", updateBindValue);
}
