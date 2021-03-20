#ifndef SELLASBUTTON_H
#define SELLASBUTTON_H

#include <QAbstractButton>
#include <QMap>

class SellasButton: public QAbstractButton
{
    Q_OBJECT
protected:
  void paintEvent(QPaintEvent  *event);

  void enterEvent(QEnterEvent *event);
  void leaveEvent(QEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

public:
    SellasButton(QWidget *parent = 0);
    ~SellasButton();

    enum class Image {
        BOSS_DIFFICULT_EASY, BOSS_DIFFICULT_NORMAL, BOSS_DIFFICULT_HARD, BOSS_DIFFICULT_CHAOS, BOSS_DIFFICULT_CANCEL
    } image;

    QPixmap *getPixmap(QString postFix);

    QPixmap *getNormal();

    QPixmap *getMouseOver();

    QPixmap *getClick();

    QPixmap *getDisable();

    void setImage(const Image &value);

private:
    static const QMap<Image, QString> imagePathMap;
    enum class State {
        NORMAL, MOUSE_OVER, CLICK, DISABLE
    } state;

    QPixmap *normal;
    QPixmap *mouseOver;
    QPixmap *click;
    QPixmap *disable;

};

#endif // SELLASBUTTON_H
