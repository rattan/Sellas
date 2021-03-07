#include "sellasimagewidget.h"

#include <QPainter>
#include <QStyle>

SellasImageWidget::SellasImageWidget(QWidget *parent): QWidget(parent)
{

}

void SellasImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    style()->drawItemPixmap(&painter, rect(), Qt::AlignCenter, this->imagePixmap.scaled(rect().size()));
}

QPixmap SellasImageWidget::pixmap() const
{
    return imagePixmap;
}

void SellasImageWidget::setPixmap(const QPixmap &pixmap)
{
    imagePixmap = pixmap;
    update();
}
