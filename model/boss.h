#ifndef BOSS_H
#define BOSS_H

#include "uidata.h"

#include <QJsonObject>
#include <QList>
#include <QPair>
#include <QPixmap>
#include <QString>

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

    Boss(QJsonObject json): imagePixmap(nullptr) {
        initFromJson(json);
    }
    ~Boss() {
        if(this->imagePixmap != nullptr) {
            delete this->imagePixmap;
        }
    }
    QString getName() const;
    QString getImage() const;
    QPixmap getImagePixmap();
    QPixmap getImageGrayScaledPixmap();
    QList<Difficult> getDifficultList() const;
    QJsonObject toJson() const;

protected:
    void initFromJson(QJsonObject json);

private:
    QString name;
    QString image;
    QPixmap *imagePixmap;
    QList<Difficult> difficultList;

};

#endif // BOSS_H
