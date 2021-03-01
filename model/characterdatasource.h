#ifndef CHARACTERDATASOURCE_H
#define CHARACTERDATASOURCE_H

#include "character.h"

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

    Requests requests;
};

#endif // CHARACTERDATASOURCE_H
