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
    explicit CharacterWidget(const Character &character, QWidget *parent = nullptr);
    ~CharacterWidget();

private:
    Ui::CharacterWidget *ui;
    const Character &characterData;
};

#endif // CHARACTERWIDGET_H
