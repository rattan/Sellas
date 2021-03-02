#include "sellaslineedit.h"

#include <QEvent>
#include <QInputMethodEvent>
#include <QKeyEvent>

SellasLineEdit::SellasLineEdit(QWidget *parent): QLineEdit(parent)
{
}

QString SellasLineEdit::text()
{
    return QLineEdit::text().left(this->cursorPosition()) + this->inputMethodEventPreeditString + QLineEdit::text().mid(this->cursorPosition());
}

void SellasLineEdit::inputMethodEvent(QInputMethodEvent *e)
{
    this->inputMethodEventPreeditString = e->preeditString();
    QLineEdit::inputMethodEvent(e);
    emit textEdited(this->text());
}
