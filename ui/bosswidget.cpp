#include "bosswidget.h"
#include "ui_bosswidget.h"

void BossWidget::difficultCancelButtonClick(bool checked)
{
    qDebug()<<"difficultCancelButtonClick";
    QString bossName = bossData.getName();
    SellasButton* buttonSender = qobject_cast<SellasButton*>(sender());
    QString difficult = buttonSender->text();
    qDebug()<<difficult;
    emit clearBossCancel(bossName, difficult);
    setClear(difficult, false);
    for(auto const &shareDifficult: this->difficultButtonMap.value(difficult, ButtonContainer(nullptr, nullptr, QList<QString>())).getClearShare()) {
        emit clearBossCancel(bossName, shareDifficult);
        setClear(shareDifficult, false);
    }
}

void BossWidget::difficultButtonClick(bool checked)
{
    qDebug()<<"difficultButtonClick";
    QString bossName = bossData.getName();
        qDebug()<<bossData.toString();
    SellasButton* buttonSender = qobject_cast<SellasButton*>(sender());
    QString difficult = buttonSender->text();
    qDebug()<<difficult;
    emit clearBoss(bossName, difficult);
    setClear(difficult, true);
    for(auto const &shareDifficult: this->difficultButtonMap.value(difficult, ButtonContainer(nullptr, nullptr, QList<QString>())).getClearShare()) {
        emit clearBoss(bossName, shareDifficult);
        setClear(shareDifficult, true);
    }
}

BossWidget::BossWidget(Boss &boss, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BossWidget),
    bossData(boss)
{
    ui->setupUi(this);
    for(auto const &difficult: bossData.getDifficultList()) {
        SellasButton *difficultButton = nullptr;
        SellasButton *cancelButton = nullptr;
        if("easy" == difficult.getName()) {
            difficultButton = ui->difficultButton1;
            difficultButton->setImage(SellasButton::Image::BOSS_DIFFICULT_EASY);
            cancelButton = ui->difficultCancelButton1;
        } else if("normal" == difficult.getName()) {
            difficultButton = ui->difficultButton2;
            difficultButton->setImage(SellasButton::Image::BOSS_DIFFICULT_NORMAL);
            cancelButton = ui->difficultCancelButton2;
        } else if("hard" == difficult.getName() || "chaos" == difficult.getName()) {
            difficultButton = ui->difficultButton3;
            if("hard" == difficult.getName()) {
                difficultButton->setImage(SellasButton::Image::BOSS_DIFFICULT_HARD);
            } else if("chaos" == difficult.getName()) {
                difficultButton->setImage(SellasButton::Image::BOSS_DIFFICULT_CHAOS);
            }
            cancelButton = ui->difficultCancelButton3;
        }

        if(difficultButton != nullptr && cancelButton != nullptr) {
            difficultButtonMap.insert(difficult.getName(), ButtonContainer(difficultButton, cancelButton, difficult.getClearShare()));
            difficultButton->setText(difficult.getName());
            difficultButton->raise();
            difficultButton->setVisible(true);
            connect(difficultButton, &SellasButton::clicked, this, &BossWidget::difficultButtonClick);

            cancelButton->setImage(SellasButton::Image::BOSS_DIFFICULT_CANCEL);
            cancelButton->setText(difficult.getName());
            cancelButton->raise();
            cancelButton->setVisible(true);
            cancelButton->setDisabled(true);
            connect(cancelButton, &SellasButton::clicked, this, &BossWidget::difficultCancelButtonClick);
        } else {
            difficultButton->setVisible(false);
            cancelButton->setVisible(false);
        }
    }
    ui->bossImageWidget->setPixmap(bossData.getImagePixmap());
}

void BossWidget::setClear(QString difficult, bool clear)
{
    ButtonContainer button = difficultButtonMap.value(difficult, ButtonContainer(nullptr, nullptr, QList<QString>()));
    if(button.getDifficultButton() != nullptr && button.getCancelButton() != nullptr) {
        button.getDifficultButton()->setDisabled(clear);
        button.getCancelButton()->setDisabled(!clear);
    }
}

void BossWidget::clear()
{
    for(auto difficult: difficultButtonMap.keys()) {
        setClear(difficult, false);
    }
}

BossWidget::~BossWidget()
{
    delete ui;
}

Boss BossWidget::getBossData() const
{
    return bossData;
}

SellasButton* BossWidget::ButtonContainer::getDifficultButton() const
{
    return difficultButton;
}

SellasButton* BossWidget::ButtonContainer::getCancelButton() const
{
    return cancelButton;
}

QList<QString> BossWidget::ButtonContainer::getClearShare() const
{
    return clearShare;
}
