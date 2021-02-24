#ifndef BOSSLISTWIDGETITEM_H
#define BOSSLISTWIDGETITEM_H

#include <QBoxLayout>
#include <QListWidgetItem>

#include <model/boss.h>

QT_BEGIN_NAMESPACE
namespace Ui { class BossWidget; }
QT_END_NAMESPACE

class BossListWidgetItem : public QWidget
{
    Q_OBJECT
private:
    QBoxLayout layout;
    Ui::BossWidget *ui;

public:
    BossListWidgetItem(Boss boss, QWidget *parent = nullptr);
    ~BossListWidgetItem();
};

#endif // BOSSLISTWIDGETITEM_H
