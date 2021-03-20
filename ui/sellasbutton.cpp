#include "sellasbutton.h"

#include <QPainter>
#include <QPixmap>
#include <QDebug>

void SellasButton::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    if(isEnabled())
    {
      switch(state)
      {
      case SellasButton::State::NORMAL:
        painter.drawPixmap(0, 0, *getNormal());
        break;
      case SellasButton::State::MOUSE_OVER:
        painter.drawPixmap(0, 0, *getMouseOver());
        break;
      case SellasButton::State::CLICK:
        painter.drawPixmap(0, 0, *getClick());
        break;
      case SellasButton::State::DISABLE:
          qDebug()<<"could not reach here.";
          break;
      }
    }
    else
    {
      if(SellasButton::State::DISABLE == state) painter.drawPixmap(0, 0, *getDisable());
    }
}

void SellasButton::enterEvent(QEnterEvent *event)
{
    Q_UNUSED(event);
    this->state = SellasButton::State::MOUSE_OVER;
    update();
}

void SellasButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->state = SellasButton::State::NORMAL;
    update();
}

void SellasButton::mousePressEvent(QMouseEvent *event)
{
    QAbstractButton::mousePressEvent(event);
    Q_UNUSED(event);
    this->state = SellasButton::State::CLICK;
    update();
}

void SellasButton::mouseReleaseEvent(QMouseEvent *event)
{
    QAbstractButton::mouseReleaseEvent(event);
    Q_UNUSED(event);

    if(underMouse()) this->state = SellasButton::State::MOUSE_OVER;
    else this->state = SellasButton::State::NORMAL;
    update();
}

SellasButton::SellasButton(QWidget *parent): QAbstractButton(parent)
{
    this->normal = this->mouseOver = this->click = this->disable = nullptr;
    this->state = SellasButton::State::NORMAL;
}

SellasButton::~SellasButton()
{
    if(this->normal != nullptr) {
        delete this->normal;
    }
    if(this->mouseOver != nullptr) {
        delete this->mouseOver;
    }
    if(this->click != nullptr) {
        delete this->click;
    }
    if(this->disable != nullptr) {
        delete this->disable;
    }
}

void SellasButton::setImage(const Image &value)
{
    image = value;
    this->update();
}

QPixmap *SellasButton::getPixmap(QString postFix)
{
    return new QPixmap(imagePathMap.value(image) + postFix);
}

QPixmap *SellasButton::getNormal()
{
    if(this->normal == nullptr) {
        this->normal = getPixmap(".png");
    }
    return normal;
}

QPixmap *SellasButton::getMouseOver()
{

    if(this->mouseOver == nullptr) {
        this->mouseOver = getPixmap("_mouse_over.png");
    }
    return mouseOver;

}

QPixmap *SellasButton::getClick()
{
    if(this->click == nullptr) {
        this->click = getPixmap("_click.png");
    }
    return click;
}

QPixmap *SellasButton::getDisable()
{

    if(this->disable == nullptr) {
        this->disable = getPixmap("_disable.png");
    }
    return disable;

}

const QMap<SellasButton::Image, QString> SellasButton::imagePathMap{
    { SellasButton::Image::BOSS_DIFFICULT_EASY, ":/images/ui/button/boss_difficult/images/ui/button/boss_difficult/boss_difficult_easy" },
    { SellasButton::Image::BOSS_DIFFICULT_NORMAL, ":/images/ui/button/boss_difficult/images/ui/button/boss_difficult/boss_difficult_normal" },
    { SellasButton::Image::BOSS_DIFFICULT_HARD, ":/images/ui/button/boss_difficult/images/ui/button/boss_difficult/boss_difficult_hard" },
    { SellasButton::Image::BOSS_DIFFICULT_CHAOS, ":/images/ui/button/boss_difficult/images/ui/button/boss_difficult/boss_difficult_chaos" },
    { SellasButton::Image::BOSS_DIFFICULT_CANCEL, ":/images/ui/button/boss_difficult_cancel/images/ui/button/boss_difficult_cancel/boss_difficult_cancel"},
};

