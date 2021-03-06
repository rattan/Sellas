#include "uidata.h"

#include <QJsonDocument>

QString UiData::toString()
{
    QJsonDocument(this->toJson()).toJson(QJsonDocument::Compact);
}

void UiData::initFromJson(QJsonObject json)
{
}
