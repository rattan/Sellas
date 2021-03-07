#ifndef CHARACTERDATASOURCE_H
#define CHARACTERDATASOURCE_H

#include "character.h"
#include "sellas.h"

#include <QMap>
#include <QString>

#include <http/requests.h>



class CharacterDataSource
{
public:
    CharacterDataSource();

    void insertCharacter(const Character character);
    Character getCharacter(const QString name);
    Character getCharacterFromWeb(const QString name);
    QList<Character> getAllCharacters();
    void updateCharacter(const QString name, const Character character);
    void removeCharacter(const QString name);

private:
    const QMap<QString, QVariant> getCharacterBindValues(Character character);
    const Character parseCharacterFromWeb(QNetworkReply* reply);
    const QPixmap getAvatarImage(QString avatarUrl);

    Requests requests;
    QMap<int, QString> serverIndexMap;
};

#endif // CHARACTERDATASOURCE_H
