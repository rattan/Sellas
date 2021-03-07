#ifndef SELLASIMAGEWIDGET_H
#define SELLASIMAGEWIDGET_H

#include <QWidget>

class SellasImageWidget : public QWidget
{
    Q_OBJECT
public:
    SellasImageWidget(QWidget *parent = 0);

    QPixmap pixmap() const;
    void setPixmap(const QPixmap &pixmap);

protected:
    void paintEvent(QPaintEvent* event);

private:
    QPixmap imagePixmap;
};

#endif // SELLASIMAGEWIDGET_H
