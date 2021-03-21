#include <QObject>
#include <QtTest/QtTest>
#include <http/requests.h>
#include <model/characterdatasource.h>
#include <model/datedatasource.h>
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

}

QTEST_MAIN(Test)
#include "test.moc"
