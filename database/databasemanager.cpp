#include "databasemanager.h"

#include <QThread>

DatabaseManager::DatabaseManager()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(DB_FILE_PATH);

    if(database.open()){
         qDebug() << "success DB connection";
         QSqlQuery query(database);
         query.exec(TABLE_COUNT_QUERY);
         query.first();
         if(query.value(0).toInt() == 0) {
             this->createTables();
         }
     } else {
         qDebug() << "fail DB connection";
     }
}

DatabaseManager::~DatabaseManager() {
    database.close();
}

void DatabaseManager::createTables()
{
    QSqlQuery query(database);
    query.exec(CREATE_TABLE_CHARACTER_QUERY);
    query.exec(CREATE_TABLE_BOSS_QUERY);
    qDebug()<<"Create tables";
}
