#include "sellaslabel.h"

#include <QPainter>
#include <QStyle>

SellasLabel::SellasLabel(QWidget *parent): QLabel(parent)
{

}

void SellasLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    style()->drawItemPixmap(&painter, rect(), Qt::AlignCenter, this->pixmap().scaled(rect().size()));
}
