#ifndef SERVER_H
#define SERVER_H

#include "uidata.h"

#include <QJsonObject>
#include <QPixmap>
#include <QString>



class Server: public UiData
{
public:
    Server(QJsonObject json) {
        this->initFromJson(json);
    }
    int getIndex() const;
    QString getName() const;
    QPixmap getIcon() const;
    QPixmap getIconPixmap() const;
    QJsonObject toJson() const;

protected:
    void initFromJson(QJsonObject json);

private:
    int index;
    QString name;
    QString icon;
    QPixmap iconPixmap;
};

#endif // SERVER_H
