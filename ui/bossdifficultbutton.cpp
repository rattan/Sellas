#include "bossdifficultbutton.h"

void BossDifficultButton::paintEvent(QPaintEvent *event)
{

}

void BossDifficultButton::enterEvent(QEnterEvent *event)
{

}

void BossDifficultButton::leaveEvent(QEvent *event)
{

}

void BossDifficultButton::mousePressEvent(QMouseEvent *event)
{

}

void BossDifficultButton::mouseReleaseEvent(QMouseEvent *event)
{

}

BossDifficultButton::BossDifficultButton()
{
    this->type = Type::NONE;
    this->state = State::NORMAL;
}

void BossDifficultButton::setType(QString type)
{
    if(type == "easy") this->type = Type::EASY;
    else if(type == "normal") this->type = Type::NORMAL;
    else if(type == "hard") this->type = Type::HARD;
    else if(type == "chaos") this->type = Type::CHAOS;
    else this->type = Type::NONE;
}
