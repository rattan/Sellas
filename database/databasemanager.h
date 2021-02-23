#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

#define DB_FILE_PATH "data.db"

/* query string */
// for sqlite
#define TABLE_COUNT_QUERY "SELECT COUNT(type) FROM sqlite_master WHERE type='table'"

// create tables
#define CREATE_TABLE_CHARACTER_QUERY R"(CREATE TABLE "character" (\
"name"	NUMERIC NOT NULL UNIQUE,\
"server"	TEXT NOT NULL,\
"level"	INTEGER NOT NULL,\
"exp"	INTEGER,\
"popularity"	INTEGER NOT NULL,\
"job"	TEXT NOT NULL,\
"job_detail"	TEXT NOT NULL,\
"guild"	TEXT,\
"avatar_cache"	NUMERIC,\
"avatar_web"	TEXT,\
PRIMARY KEY("name")\
))"
#define CREATE_TABLE_BOSS_QUERY R"(CREATE TABLE "boss" (\
"character_name"	TEXT NOT NULL,\
"name"	TEXT NOT NULL,\
"difficulty"	TEXT NOT NULL,\
"clear_date"	INTEGER,\
FOREIGN KEY("character_name") REFERENCES "character"("name")\
))"


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
    static DatabaseManager& getIncetance() {
        static DatabaseManager s;
        return s;
    }

//    QSqlQuery query(QStringList projection, QString selection, QStringList selectionArgs, QString sortOrder);
//    int update(QString selection, QStringList selectionArgs, QMap<QString, QString> values);
//    int remove(QString selection, QString selectionArgs);
};

#endif // DATABASEMANAGER_H
