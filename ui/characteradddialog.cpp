#include "characteradddialog.h"
#include "ui_characteradddialog.h"

#include <QCompleter>
#include <QIcon>
#include <QLineEdit>
#include <QPainter>

CharacterAddDialog::CharacterAddDialog(const Sellas &sellas, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::CharacterAddDialog),
    sellas(sellas)
{
    ui->setupUi(this);
    connect(ui->makePushButtom, &QPushButton::clicked, this, &CharacterAddDialog::accept);
    connect(ui->cancelPushButton, &QPushButton::clicked, this, &CharacterAddDialog::reject);

    connect(ui->jobComboBox, &QComboBox::currentIndexChanged, this, &CharacterAddDialog::jobSelected);
    ui->jobDetailComboBox->setDisabled(true);

    connect(ui->nameLineEdit, &QLineEdit::textEdited, this, &CharacterAddDialog::nameChange);
    ui->nameLineEdit->setInputMethodHints(Qt::InputMethodHint::ImhNoTextHandles);
    connect(&nameChangeTimer, &QTimer::timeout, this, &CharacterAddDialog::nameCheck);
    nameChangeTimer.setInterval(200);
    nameChangeTimer.setSingleShot(true);

    initFromSellas();
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
                     ui->characterImageWidget->pixmap(),
                     avatarUrl);
}

void CharacterAddDialog::initFromSellas()
{
    this->ui->serverComboBox->clear();
    for(auto server: sellas.getServerList()) {
        this->ui->serverComboBox->addItem(QIcon(server.getImagePixmap()), server.getName());
    }

    this->ui->jobComboBox->clear();
    this->ui->jobDetailComboBox->clear();
    for(auto job: sellas.getJobList()) {
        this->ui->jobComboBox->addItem(job.first);
        this->jobDetailMap.insert(job.first, job.second);
    }
}

void CharacterAddDialog::setCharacterData(Character &character)
{
    if(!character.getName().isEmpty()) {
        ui->nameLineEdit->setText(character.getName());
        ui->levelSpinBox->setValue(character.getLevel());
        ui->expSpinBox->setValue(character.getExp());
        ui->popularitySpinBox->setValue(character.getPopularity());
        ui->guildLineEdit->setText(character.getGuild());
        this->ui->serverComboBox->setCurrentText(character.getServer());

        //job, jobdetail
        this->ui->jobComboBox->setCurrentText(character.getJob());
        jobSelected(ui->jobComboBox->currentIndex());
        this->ui->jobDetailComboBox->setCurrentText(character.getJobDetail());
        ui->characterImageWidget->setPixmap(character.getAvatar());
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

void CharacterAddDialog::jobSelected(int index)
{
    ui->jobDetailComboBox->clear();
    QList<QString> jobDetail = jobDetailMap[ui->jobComboBox->currentText()];
    for(auto jobDetail: jobDetail) {
        ui->jobDetailComboBox->addItem(jobDetail);
    }
    if(jobDetail.size() == 1) {
        ui->jobDetailComboBox->setCurrentIndex(0);
    }
    ui->jobDetailComboBox->setEnabled(true);
}
