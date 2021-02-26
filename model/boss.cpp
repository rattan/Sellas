#include "boss.h"

#include <qjsonvalue.h>

#include <QJsonArray>
#include <QPixmap>

QString Boss::getName() const
{
    return name;
}

QString Boss::getImage() const
{
    return image;
}

QPixmap Boss::getImagePixmap()
{
    if(this->imagePixmap == nullptr) {
        this->imagePixmap = new QPixmap(this->image);
    }
    return *this->imagePixmap;
}

QPixmap Boss::getImageGrayScaledPixmap()
{
    return QPixmap::fromImage(this->getImagePixmap().toImage().convertToFormat(QImage::Format::Format_Grayscale8));
}

QList<Boss::Difficult> Boss::getDifficultList() const
{
    return difficultList;
}

void Boss::initFromJson(QJsonObject json)
{
    name = json.value("name").toString();
    image = json.value("image").toString();
    for(auto difficultRef: json.value("difficult").toArray()) {
        QJsonObject difficultObject = difficultRef.toObject();
        QString name = difficultObject.value("name").toString();
        QString cycle = difficultObject.value("cycle").toString();
        int min_level = difficultObject.value("min_level").toInt();
        int max_level = difficultObject.value("min_level").toInt();
        QList<QString> clearShare;
        for(auto clear: difficultObject.value("clear_share").toArray()) {
            clearShare.append(clear.toString());
        }
        Boss::Difficult difficult(name, cycle, min_level, max_level, clearShare);
        this->difficultList.append(difficult);
    }
}

QJsonObject Boss::toJson() const
{
    QJsonObject bossObject;
    bossObject.insert("name", QJsonValue(this->name));
    bossObject.insert("image", QJsonValue(this->image));
    QJsonArray difficultArray;
    for(auto difficult: this->difficultList) {
        QJsonObject difficultObject;
        difficultObject.insert("name", difficult.getName());
        difficultObject.insert("cycle", difficult.getCycle());
        difficultObject.insert("min_level", difficult.getMin_level());
        difficultObject.insert("max_level", difficult.getMax_level());
        QJsonArray clearShareList;
        for(auto clearShare: difficult.getClearShare()) {
            clearShareList.append(clearShare);
        }
        difficultObject.insert("clear_share", clearShareList);
        difficultArray.append(difficultObject);
    }
    bossObject.insert("difficult", difficultArray);
    return bossObject;
}

Boss::Boss(QJsonObject json)
{
    initFromJson(json);
    this->imagePixmap = nullptr;
}

Boss::~Boss()
{
    if(this->imagePixmap) {
        delete this->imagePixmap;
    }
}

Boss::Difficult::Difficult(QString name, QString cycle, int min_level, int max_level, QList<QString> clearShare):
    name(name), cycle(cycle), min_level(min_level), max_level(max_level), clearShare(clearShare)
{
}

QList<QString> Boss::Difficult::getClearShare() const
{
    return clearShare;
}

int Boss::Difficult::getMax_level() const
{
    return max_level;
}

int Boss::Difficult::getMin_level() const
{
    return min_level;
}

QString Boss::Difficult::getCycle() const
{
    return cycle;
}

QString Boss::Difficult::getName() const
{
    return name;
}
