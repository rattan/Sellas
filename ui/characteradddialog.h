#ifndef CHARACTERADDDIALOG_H
#define CHARACTERADDDIALOG_H

#include <QDialog>
#include <QString>

#include <model/character.h>

namespace Ui {
class CharacterAddDialog;
}

class CharacterAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterAddDialog(QDialog *parent = nullptr);
    ~CharacterAddDialog();

    Character getCharacter();

private:
    Ui::CharacterAddDialog *ui;
    QString avatarCache;
    QString avatarWeb;
};

#endif // CHARACTERADDDIALOG_H
