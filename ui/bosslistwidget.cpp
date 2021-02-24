#include "bosslistwidget.h"
#include "ui_bosslistwidget.h"

BossListWidget::BossListWidget(Boss &boss, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BossListWidget),
    bossData(boss)
{
    ui->setupUi(this);
    ui->bossImageLabel->setPixmap(bossData.getImagePixmap());

}

BossListWidget::~BossListWidget()
{
    delete ui;
}
