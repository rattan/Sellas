#include "sellas.h"

#include <QJsonArray>
#include <QJsonDocument>

QList<Boss> Sellas::getBossList() const
{
    return bossList;
}

QString Sellas::getDatabase() const
{
    return database;
}

QString Sellas::getVersion() const
{
    return version;
}

QString Sellas::getName() const
{
    return name;
}

Sellas::Sellas(QJsonObject json)
{
    this->name = json.value("name").toString();
    this->version = json.value("version").toString();
    this->database = json.value("database").toString();
    for(auto boss: json.value("boss").toArray()) {
        bossList.append(Boss(boss.toObject()));
    }
}

QJsonObject Sellas::toJson()
{
    QJsonObject json;
    json.insert("name", QJsonValue(this->name));
    json.insert("version", QJsonValue(this->version));
    json.insert("database", QJsonValue(this->database));
    QJsonArray bossArrayObject;
    for(auto boss: this->bossList) {
        bossArrayObject.append(boss.toJson());
    }
    json.insert("boss", bossArrayObject);
    return json;
}

QString Sellas::toString()
{
    return QJsonDocument(this->toJson()).toJson(QJsonDocument::Compact);
}
