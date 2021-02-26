#ifndef CHARACTERDATASOURCE_H
#define CHARACTERDATASOURCE_H

#include "character.h"

#include <QString>



class CharacterDataSource
{
public:
    CharacterDataSource();

    void insertCharacter(const Character character);
    Character getCharacter(const QString name);
    QList<Character> getAllCharacters();
    void updateCharacter(const QString name, const Character character);
    void removeCharacter(const QString name);

private:
    const QMap<QString, QVariant> getCharacterBindValues(Character character);
};

#endif // CHARACTERDATASOURCE_H
