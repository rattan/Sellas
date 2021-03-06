#include "server.h"

void Server::initFromJson(QJsonObject json)
{
    this->index = json.value("index").toInt();
    this->name = json.value("name").toString();
    this->image = json.value("image").toString();
    this->imagePixmap = QPixmap(image);
}

QPixmap Server::getImagePixmap() const
{
    return imagePixmap;
}

QPixmap Server::getImage() const
{
    return image;
}

QJsonObject Server::toJson() const
{
    QJsonObject serverObject;
    serverObject.insert("index", QJsonValue(this->index));
    serverObject.insert("name", QJsonValue(this->name));
    serverObject.insert("image", QJsonValue(this->image));
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
