#include "characteradddialog.h"
#include "ui_characteradddialog.h"

CharacterAddDialog::CharacterAddDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::CharacterAddDialog)
{
    ui->setupUi(this);
    connect(ui->makePushButtom, &QPushButton::clicked, this, &CharacterAddDialog::accept);
    connect(ui->cancelPushButton, &QPushButton::clicked, this, &CharacterAddDialog::reject);
}

CharacterAddDialog::~CharacterAddDialog()
{
    delete ui;
}

Character CharacterAddDialog::getCharacter()
{
    return Character(ui->nameLineEdit->text(),
                     ui->serverComboBox->currentText(),
                     ui->levelSpinBox->text().toInt(),
                     ui->expSpinBox->text().toULongLong(),
                     ui->popularitySpinBox->text().toInt(),
                     ui->jobComboBox->currentText(),
                     ui->jobDetailComboBox->currentText(),
                     ui->guildLineEdit->text(),
                     avatarCache,
                     avatarWeb);
}
