#include "uidata.h"

#include <QJsonDocument>

QString UiData::toString() const
{
    return QJsonDocument(toJson()).toJson(QJsonDocument::Compact);
}

void UiData::initFromJson(QJsonObject json)
{
}
