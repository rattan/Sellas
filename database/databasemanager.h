#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMap>

#define DB_FILE_PATH "data.db"

/* query string */
// for sqlite
#define TABLE_COUNT_QUERY "SELECT COUNT(type) FROM sqlite_master WHERE type='table'"

// create tables
#define CREATE_TABLE_CHARACTER_QUERY R"*(CREATE TABLE "character" ("name" NUMERIC NOT NULL UNIQUE,"server" TEXT NOT NULL,"level" INTEGER NOT NULL,"exp" INTEGER,"popularity" INTEGER NOT NULL,"job" TEXT NOT NULL,"job_detail" TEXT NOT NULL,"guild" TEXT,"avatar" BLOB,"avatar_url" TEXT,PRIMARY KEY("name")))*"
#define CREATE_TABLE_BOSS_QUERY R"*(CREATE TABLE "boss" ("character_name" TEXT NOT NULL,"name" TEXT NOT NULL,"difficulty" TEXT NOT NULL,"clear_date" INTEGER,FOREIGN KEY("character_name") REFERENCES "character"("name")))*"

class DatabaseManager: public QObject
{
    Q_OBJECT
private:
    QSqlDatabase database;
    DatabaseManager();
    DatabaseManager(const DatabaseManager& ref) = delete;
    DatabaseManager& operator=(const DatabaseManager& ref) = delete;
    ~DatabaseManager();
    void createTables();

public:
    static DatabaseManager& getInsetance() {
        static DatabaseManager s;
        return s;
    }

    QSqlQuery query(const QString queryString, const QMap<QString, QVariant> bindValues = QMap<QString, QVariant>());
};

#endif // DATABASEMANAGER_H
