#ifndef SELLAS_H
#define SELLAS_H

#include "boss.h"
#include "server.h"

#include <QJsonObject>
#include <QPair>
#include <QString>



class Sellas: public UiData
{
private:
    QString name;
    QString version;
    QString database;
    QList<Boss> bossList;
    QList<Server> serverList;
    QList<QPair<QString, QList<QString>>> jobList;

public:
    Sellas(QJsonObject json) {
        this->initFromJson(json);
    }

    QJsonObject toJson() const;
    QList<Boss> getBossList() const;
    QString getDatabase() const;
    QString getVersion() const;
    QString getName() const;
    QList<Server> getServerList() const;
    QList<QPair<QString, QList<QString> > > getJobList() const;

protected:
    void initFromJson(QJsonObject json);
};

#endif // SELLAS_H
