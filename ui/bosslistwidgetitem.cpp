#include "bosslistwidgetitem.h"

#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <ui_Boss.h>

BossListWidgetItem::BossListWidgetItem(Boss boss, QWidget *parent): layout(QBoxLayout::TopToBottom), QWidget(parent), ui(new Ui::BossWidget)
{
    ui->setupUi(this);
QPixmap bossPixmap = boss.getImagePixmap();
ui->bossImageLabel->setPixmap(bossPixmap);
QLabel *label = new QLabel;
label->setPixmap(bossPixmap);
layout.addWidget(label);
layout.setSizeConstraint(QBoxLayout::SetFixedSize);
this->setBaseSize(242, 263);
setFixedWidth(242);
setFixedHeight(263);
//this->setLayout(&layout);
}

BossListWidgetItem::~BossListWidgetItem()
{
    delete ui;
}
