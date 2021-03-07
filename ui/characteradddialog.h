#ifndef CHARACTERADDDIALOG_H
#define CHARACTERADDDIALOG_H

#include <QDialog>
#include <QString>
#include <QTimer>

#include <model/character.h>
#include <model/characterdatasource.h>
#include <model/sellas.h>
#include <model/server.h>

namespace Ui {
class CharacterAddDialog;
}

class CharacterAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterAddDialog(const Sellas &sellas, QDialog *parent = nullptr);
    ~CharacterAddDialog();

    Character getCharacter();


private:
    Ui::CharacterAddDialog *ui;
    QString avatarUrl;
    QTimer nameChangeTimer;
    CharacterDataSource characterDataSource;
    const Sellas &sellas;
    QMap<QString, QList<QString>> jobDetailMap;


    void setCharacterData(Character &character);
    void initFromSellas();

private slots:
    void nameChange(const QString &name);
    void nameCheck();
    void jobSelected(int index);
};

#endif // CHARACTERADDDIALOG_H
