#ifndef SELLAS_H
#define SELLAS_H

#include "boss.h"

#include <QJsonObject>
#include <QString>



class Sellas
{
private:
    QString name;
    QString version;
    QString database;
    QList<Boss> bossList;

public:
    Sellas(QJsonObject json);

    QJsonObject toJson();
    QString toString();
    QList<Boss> getBossList() const;
    QString getDatabase() const;
    QString getVersion() const;
    QString getName() const;
};

#endif // SELLAS_H
