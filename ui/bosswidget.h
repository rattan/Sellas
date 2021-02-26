#ifndef BOSSWIDGET_H
#define BOSSWIDGET_H

#include "sellasbutton.h"

#include <QPushButton>
#include <QWidget>
#include <tuple>

#include <model/boss.h>

namespace Ui {
class BossWidget;
}

class BossWidget : public QWidget
{
    Q_OBJECT
private slots:
    void difficultCancelButtonClick(bool checked);
public:
    explicit BossWidget(Boss &boss, QWidget *parent = nullptr);
    ~BossWidget();

private:
    Ui::BossWidget *ui;
    Boss &bossData;
    QMap<QString, std::tuple<QPushButton*, SellasButton*, Boss::Difficult*>> difficultButtonMap;
};

#endif // BOSSWIDGET_H
