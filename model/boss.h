#ifndef BOSS_H
#define BOSS_H

#include <QJsonObject>
#include <QList>
#include <QPair>
#include <QPixmap>
#include <QString>

class Boss
{
private:
    QString name;
    QString image;
    QPixmap *imagePixmap;
    QList<QPair<QString, QString>> difficulty;
public:
    Boss(QJsonObject json);
    ~Boss();
    QString getName() const;
    QString getImage() const;
    QPixmap getImagePixmap();
    QPixmap getImageGrayScaledPixmap();
    QList<QPair<QString, QString> > getDifficulty() const;
};

#endif // BOSS_H
