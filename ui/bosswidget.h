#ifndef BOSSWIDGET_H
#define BOSSWIDGET_H

#include "sellasbutton.h"

#include <QPushButton>
#include <QWidget>

#include <model/boss.h>

namespace Ui {
class BossWidget;
}

class BossWidget : public QWidget
{
    Q_OBJECT
private slots:
    void difficultCancelButtonClick();
public:
    explicit BossWidget(Boss &boss, QWidget *parent = nullptr);
    ~BossWidget();

private:
    Ui::BossWidget *ui;
    Boss &bossData;
    QMap<QString, QPushButton*> difficultButtonMap;
    QMap<QString, SellasButton*> cancelButtonMap;
};

#endif // BOSSWIDGET_H
