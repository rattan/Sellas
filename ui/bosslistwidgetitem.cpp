#include "bosslistwidgetitem.h"

#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>

BossListWidgetItem::BossListWidgetItem(Boss boss):layout(QBoxLayout::TopToBottom)
{
    QPushButton *button = new QPushButton("TEST");
layout.addWidget(button);
QLabel *label = new QLabel(boss.getName());
QPixmap bossPixmap = boss.getImagePixmap();


label->setPixmap(bossPixmap);
layout.addWidget(label);
layout.setSizeConstraint(QBoxLayout::SetFixedSize);
this->setLayout(&layout);
}
