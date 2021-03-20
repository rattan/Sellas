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
    setClearImpl(button, clear);
    for(auto const &shareDifficult: button.getClearShare()) {
        setClearImpl(difficultButtonMap.value(shareDifficult, ButtonContainer(nullptr, nullptr, QList<QString>())), clear);
    }
}

BossWidget::~BossWidget()
{
    delete ui;
}

void BossWidget::setClearImpl(ButtonContainer button, bool clear)
{
    if(button.getDifficultButton() != nullptr && button.getCancelButton() != nullptr) {
        button.getDifficultButton()->setDisabled(clear);
        button.getCancelButton()->setDisabled(!clear);
    }
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
