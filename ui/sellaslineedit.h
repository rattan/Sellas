#ifndef SELLASLINEEDIT_H
#define SELLASLINEEDIT_H

#include <QLineEdit>

class SellasLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    SellasLineEdit(QWidget *parent = 0);

    QString text();

protected:
    void inputMethodEvent(QInputMethodEvent *) override;

private:
    QString inputMethodEventPreeditString;
};

#endif // SELLASLINEEDIT_H
