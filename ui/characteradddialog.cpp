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
                     avatarCache,
                     avatarWeb);
}

void CharacterAddDialog::nameChange(const QString &name)
{
    ui->makePushButtom->setDisabled(true);
    this->nameChangeTimer.start();
    qDebug()<<"nameChange";
}

void CharacterAddDialog::nameCheck()
{
    qDebug()<<"nameCheck " << ui->nameLineEdit->text();
    ui->makePushButtom->setEnabled(true);
}
