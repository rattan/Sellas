#ifndef BOSSLISTWIDGETITEM_H
#define BOSSLISTWIDGETITEM_H

#include <QBoxLayout>
#include <QListWidgetItem>

#include <model/boss.h>

class BossListWidgetItem : public QWidget
{
private:
    QBoxLayout layout;
public:
    BossListWidgetItem(Boss boss);
};

#endif // BOSSLISTWIDGETITEM_H
