#ifndef BOSS_H
#define BOSS_H

#include <QJsonObject>
#include <QList>
#include <QPair>
#include <QPixmap>
#include <QString>

class Boss
{
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

    Boss(QJsonObject json);
    ~Boss();
    QString getName() const;
    QString getImage() const;
    QPixmap getImagePixmap();
    QPixmap getImageGrayScaledPixmap();
    QList<Difficult> getDifficultList() const;
    QJsonObject toJson() const;

private:
    QString name;
    QString image;
    QPixmap *imagePixmap;
    QList<Difficult> difficultList;

    void initFromJson(QJsonObject json);

};

#endif // BOSS_H
