#ifndef BOSSDIFFICULTBUTTON_H
#define BOSSDIFFICULTBUTTON_H

#include <QAbstractButton>
#include <QObject>
#include <QString>

class BossDifficultButton : public QAbstractButton
{
    Q_OBJECT

protected:
  void paintEvent(QPaintEvent  *event);

  void enterEvent(QEnterEvent *event);
  void leaveEvent(QEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
public:
    BossDifficultButton();

    enum class Type{
        NONE, EASY, NORMAL, HARD, CHAOS
    };

    enum class State {
        NORMAL, MOUSE_OVER, CLICKED, DISABL, CLEAR
    };

    void setType(QString type);

private:
    Type type;
    State state;
};

#endif // BOSSDIFFICULTBUTTON_H
