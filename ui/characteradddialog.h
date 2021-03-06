#ifndef CHARACTERADDDIALOG_H
#define CHARACTERADDDIALOG_H

#include <QDialog>
#include <QString>
#include <QTimer>

#include <model/character.h>
#include <model/characterdatasource.h>
#include <model/server.h>

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

    void setServers(const QList<Server> &serverList);

private:
    Ui::CharacterAddDialog *ui;
    QString avatarUrl;
    QTimer nameChangeTimer;
    CharacterDataSource characterDataSource;

    void setCharacterData(Character &character);

private slots:
    void nameChange(const QString &name);
    void nameCheck();
};

#endif // CHARACTERADDDIALOG_H
