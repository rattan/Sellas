#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QWidget>

#include <model/character.h>

namespace Ui {
class CharacterWidget;
}

class CharacterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterWidget(Character character, QWidget *parent = nullptr);
    ~CharacterWidget();

    const Character &getCharacterData() const;

private:
    Ui::CharacterWidget *ui;
    Character characterData;
};

#endif // CHARACTERWIDGET_H
