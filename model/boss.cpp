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

QList<QPair<QString, QString> > Boss::getDifficulty() const
{
    return difficulty;
}

Boss::Boss(QJsonObject json)
{
    name = json.value("name").toString();
    image = json.value("image").toString();
    for(auto difficult: json.value("difficulty").toArray()) {
        QJsonArray difficultArray = difficult.toArray();
        QPair<QString, QString> pair;
        pair.first = difficultArray.at(0).toString();
        pair.second = difficultArray.at(1).toString();
        this->difficulty.append(pair);
    }
    this->imagePixmap = nullptr;
}

Boss::~Boss()
{
    if(this->imagePixmap) {
        delete this->imagePixmap;
    }
}
