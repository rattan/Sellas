#include "bosswidget.h"
#include "ui_bosswidget.h"

void BossWidget::difficultCancelButtonClick()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    QString difficult = buttonSender->text();

}

BossWidget::BossWidget(Boss &boss, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BossWidget),
    bossData(boss)
{
    ui->setupUi(this);
    for(auto difficult: bossData.getDifficultList()) {
        QPushButton *difficultButton = nullptr;
        SellasButton *cancelButton = nullptr;
        if("easy" == difficult.getName()) {
            difficultButton = ui->difficultButton1;
            cancelButton = ui->difficultCancelButton1;
        } else if("normal" == difficult.getName()) {
            difficultButton = ui->difficultButton2;
            cancelButton = ui->difficultCancelButton2;
        } else if("hard" == difficult.getName() || "chaos" == difficult.getName()) {
            difficultButton = ui->difficultButton3;
            cancelButton = ui->difficultCancelButton3;
        }

        if(difficultButton != nullptr) {
            difficultButtonMap.insert(difficult.getName(), difficultButton);
            difficultButton->setText(difficult.getName());
            difficultButton->raise();
            difficultButton->setVisible(true);
            qDebug()<<difficult.getName();
        }
        if(cancelButton != nullptr) {
            cancelButtonMap.insert(difficult.getName(), cancelButton);
            cancelButton->setImage(SellasButton::Image::BOSS_DIFFICULT_CANCEL);
            cancelButton->setText(difficult.getName());
            cancelButton->raise();
            cancelButton->setVisible(true);
        }
    }
    ui->bossImageLabel->setPixmap(bossData.getImagePixmap());
}

BossWidget::~BossWidget()
{
    delete ui;
}
