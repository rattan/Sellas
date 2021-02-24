#ifndef BOSSLISTWIDGET_H
#define BOSSLISTWIDGET_H

#include <QWidget>

#include <model/boss.h>

namespace Ui {
class BossListWidget;
}

class BossListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BossListWidget(Boss &boss, QWidget *parent = nullptr);
    ~BossListWidget();

private:
    Ui::BossListWidget *ui;
    Boss &bossData;
};

#endif // BOSSLISTWIDGET_H
