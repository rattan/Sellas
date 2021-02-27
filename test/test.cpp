#include <QObject>
#include <QtTest/QtTest>
#include <http/requests.h>
#include <model/characterdatasource.h>
#include <model/sellasparser.h>
#include"database/databasemanager.h"

class Test : public QObject
{
    Q_OBJECT
private slots:
    void testcode();

};


void Test::testcode()
{
//DatabaseManager::getIncetance();
//Requests req;
//qDebug()<<req.get(QNetworkRequest(QUrl("https://raw.githubusercontent.com/rattan/hook/master/hook.pro")))->readAll();
//    SellasParser parser(QFile("sellas.json"));

    CharacterDataSource cds;
    cds.insertCharacter(Character("a", "b", 1, 2, 3, "f", "g", "h", "i", "j"));

}

QTEST_MAIN(Test)
#include "test.moc"
