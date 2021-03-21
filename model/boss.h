#ifndef BOSS_H
#define BOSS_H

#include "uidata.h"

#include <QJsonObject>
#include <QList>
#include <QPair>
#include <QPixmap>
#include <QString>

#define CYCLE_DAILY "daily"
#define CYCLE_WEEKLY "weekly"
#define CYCLE_MONTHLY "monthly"

class Boss: public UiData
{
    using UiData::UiData;
public:
    class Difficult {
    private:
        friend Boss;
        Difficult(QString name, QString cycle, int min_level, int max_level, QList<QString> clearShare);

    public:
        QString getName() const;
        QString getCycle() const;
        int getMin_level() const;
        int getMax_level() const;
        QList<QString> getClearShare() const;

    private:
        QString name;
        QString cycle;
        int min_level;
        int max_level;
        QList<QString> clearShare;
    };

    class Clear {
    public:
        Clear(QString name, QString difficult, int clearDate):
            name(name), difficult(difficult), clearDate(clearDate) {}
        QString getName() const;
        QString getDifficult() const;
        int getClearDate() const;
    private:
        QString name;
        QString difficult;
        int clearDate;
    };

    Boss(QJsonObject json) {
        initFromJson(json);
    }
    QString getName() const;
    QString getImage() const;
    QPixmap getImagePixmap() const;
    QPixmap getImageGrayScaledPixmap();
    QList<Difficult> getDifficultList() const;
    QJsonObject toJson() const;

    Boss::Difficult findDifficult(QString difficult) const;

protected:
    void initFromJson(QJsonObject json);

private:
    QString name;
    QString image;
    QPixmap imagePixmap;
    QList<Difficult> difficultList;
    QMap<QString, Difficult> difficultMap;

};

#endif // BOSS_H
