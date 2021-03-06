#include "server.h"

void Server::initFromJson(QJsonObject json)
{
    this->index = json.value("index").toInt();
    this->name = json.value("name").toString();
    this->icon = json.value("icon").toString();
    this->iconPixmap = QPixmap(icon);
}

QPixmap Server::getIconPixmap() const
{
    return iconPixmap;
}

QPixmap Server::getIcon() const
{
    return icon;
}

QJsonObject Server::toJson() const
{
    QJsonObject serverObject;
    serverObject.insert("index", QJsonValue(this->index));
    serverObject.insert("name", QJsonValue(this->name));
    serverObject.insert("icon", QJsonValue(this->icon));
    return serverObject;
}

QString Server::getName() const
{
    return name;
}

int Server::getIndex() const
{
    return index;
}
