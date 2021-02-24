#include "sellaslistwidget.h"

#include <QWheelEvent>
#include <QScrollBar>
#include <QEasingCurve>
#include <QPropertyAnimation>

SellasListWidget::SellasListWidget(QObject *parent) : QListWidget(parent)
{
    animation.setStartValue(0);
    animation.setEndValue(242);
    animation.setDuration(200);
    animation.setEasingCurve(QEasingCurve::Linear);animation.
    connect(&animation, &QVariantAnimation::valueChanged, this, &SellasListWidget::scrollValueChanged);
    connect(&animation, &QVariantAnimation::finished, this, &SellasListWidget::scrollFinished);
    scrollProcessing = false;
}

void SellasListWidget::scrollValueChanged(const QVariant &value)
{
    this->horizontalScrollBar()->setValue(startPos + value.toInt());
    if(scrollQueue.size() > 0) {
        while(!scrollQueue.empty()) {
            targetPos += scrollQueue.front();
            scrollQueue.pop_front();
        }
        animation.setEndValue(242 * targetPos);
    }
}

void SellasListWidget::scrollFinished()
{
    scrollProcessing = false;
}

void SellasListWidget::wheelEvent(QWheelEvent *event)
{
    int upDown = event->angleDelta().y() > 0 ? 1 : -1;
    scrollQueue.push_back(upDown);
    if(scrollProcessing == false && scrollQueue.size() > 0) {
        scrollProcessing = true;
        startPos = this->horizontalScrollBar()->value();
//        if(startPos % 242 != 0) {
//            startPos -= startPos % 242;
//            startPos += startPos % 242 > 121 ? 242 : 0;
//        }
        targetPos = 0;
        while(!scrollQueue.empty()) {
            targetPos += scrollQueue.front();
            scrollQueue.pop_front();
        }
        animation.setEndValue(242 * targetPos);
        animation.start();
    }
    event->accept();
}
