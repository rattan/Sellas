#ifndef SELLASLISTWIDGET_H
#define SELLASLISTWIDGET_H

#include <QListWidget>
#include <QPropertyAnimation>
#include <QQueue>

class SellasListWidget : public QListWidget
{
    Q_OBJECT
    QObject * QListWidget;
    QVariantAnimation animation;
    int startPos;
    int targetPos;
    QQueue<int> scrollQueue;
    bool scrollProcessing;
public:
    explicit SellasListWidget(QObject *parent = nullptr);

private slots:
    void scrollValueChanged(const QVariant &value);
    void scrollFinished();

protected:
    void wheelEvent(QWheelEvent *event);

};

#endif // SELLASLISTWIDGET_H
