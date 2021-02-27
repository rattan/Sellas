#include "sellaslineedit.h"

#include <QEvent>
#include <QInputMethodEvent>
#include <QKeyEvent>

SellasLineEdit::SellasLineEdit(QWidget *parent): QLineEdit(parent)
{
}

QString SellasLineEdit::text()
{
    return QLineEdit::text() + this->inputMethodEventPreeditString;
}

void SellasLineEdit::inputMethodEvent(QInputMethodEvent *e)
{
    this->inputMethodEventPreeditString = e->preeditString();
    QLineEdit::inputMethodEvent(e);
    emit textEdited(this->text());
}
