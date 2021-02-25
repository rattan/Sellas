#include "bosslistwidget.h"
#include "ui_bosslistwidget.h"

BossListWidget::BossListWidget(Boss &boss, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BossListWidget),
    bossData(boss)
{
    ui->setupUi(this);
    ui->bossImageLabel->setPixmap(bossData.getImagePixmap());
    ui->difficultCancelButton1->setImage(SellasButton::Image::BOSS_DIFFICULT_CANCEL);
    ui->difficultCancelButton2->setImage(SellasButton::Image::BOSS_DIFFICULT_CANCEL);
    ui->difficultCancelButton3->setImage(SellasButton::Image::BOSS_DIFFICULT_CANCEL);
}

BossListWidget::~BossListWidget()
{
    delete ui;
}
