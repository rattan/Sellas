#ifndef SELLASLABEL_H
#define SELLASLABEL_H

#include <QLabel>

class SellasLabel : public QLabel
{
    Q_OBJECT
public:
    SellasLabel(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent* event);
};

#endif // SELLASLABEL_H
