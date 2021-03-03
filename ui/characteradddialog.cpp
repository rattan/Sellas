#include "characteradddialog.h"
#include "ui_characteradddialog.h"

#include <QCompleter>
#include <QLineEdit>

CharacterAddDialog::CharacterAddDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::CharacterAddDialog)
{
    ui->setupUi(this);
    connect(ui->makePushButtom, &QPushButton::clicked, this, &CharacterAddDialog::accept);
    connect(ui->cancelPushButton, &QPushButton::clicked, this, &CharacterAddDialog::reject);

    connect(ui->nameLineEdit, &QLineEdit::textEdited, this, &CharacterAddDialog::nameChange);
    ui->nameLineEdit->setInputMethodHints(Qt::InputMethodHint::ImhNoTextHandles);
    connect(&nameChangeTimer, &QTimer::timeout, this, &CharacterAddDialog::nameCheck);
    nameChangeTimer.setInterval(200);
    nameChangeTimer.setSingleShot(true);
}

CharacterAddDialog::~CharacterAddDialog()
{
    delete ui;
}

Character CharacterAddDialog::getCharacter()
{
    return Character(ui->nameLineEdit->text(),
                     ui->serverComboBox->currentText(),
                     ui->levelSpinBox->value(),
                     ui->expSpinBox->value(),
                     ui->popularitySpinBox->value(),
                     ui->jobComboBox->currentText(),
                     ui->jobDetailComboBox->currentText(),
                     ui->guildLineEdit->text(),
                     ui->characterImageLabel->pixmap(),
                     avatarUrl);
}

void CharacterAddDialog::setCharacterData(Character &character)
{
    if(!character.getName().isEmpty()) {
        ui->nameLineEdit->setText(character.getName());
        ui->levelSpinBox->setValue(character.getLevel());
        ui->expSpinBox->setValue(character.getExp());
        ui->popularitySpinBox->setValue(character.getPopularity());
        ui->guildLineEdit->setText(character.getGuild());
        //job, jobdetail
        ui->characterImageLabel->setPixmap(character.getAvatar());
        this->avatarUrl = character.getAvatarUrl();
    }
}

void CharacterAddDialog::nameChange(const QString &name)
{
    ui->makePushButtom->setDisabled(true);
    this->nameChangeTimer.start();
    qDebug()<<"nameChange";
}

void CharacterAddDialog::nameCheck()
{
    QString targetName = ui->nameLineEdit->text();
    qDebug()<<"nameCheck " << targetName;
    Character character = characterDataSource.getCharacter(targetName);
    if(character.getName().isEmpty()) {
        character = characterDataSource.getCharacterFromWeb(targetName);
        if(character.getName().isEmpty()) {
            // non character;
        } else {
            setCharacterData(character);
        }
        ui->makePushButtom->setEnabled(true);
    } else {
        setCharacterData(character);
    }
}
