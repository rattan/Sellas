#ifndef BOSSDATASOURCE_H
#define BOSSDATASOURCE_H

#include "boss.h"



class BossDataSource
{
public:
    BossDataSource();

public:
    void insertBossesForCharacter(QString characterName, QList<Boss> bossList);
    void clearBossNow(QString characterName, QString bossName, QString Difficulty);
    void clearBossCancel(QString characterName, QString bossName, QString Difficulty);
    Boss::Clear getBossClear(QString characterName, QString bossName, QString Difficulty);
    QList<Boss::Clear> getBossClear(QString characterName, QString bossName);

private:
    void insertBossForCharacter(QString characterName, Boss boss);

};

#endif // BOSSDATASOURCE_H
