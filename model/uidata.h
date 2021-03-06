#ifndef UIDATA_H
#define UIDATA_H

#include <QJsonObject>



class UiData
{
public:
    virtual QJsonObject toJson() const = 0;
    QString toString();

protected:
    virtual void initFromJson(QJsonObject json);
};

#endif // UIDATA_H
