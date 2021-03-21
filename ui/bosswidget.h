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
    void difficultButtonClick(bool checked);
public:
    explicit BossWidget(Boss &boss, QWidget *parent = nullptr);
    void setClear(QString difficult, bool clear);
    void clear();
    ~BossWidget();

    Boss getBossData() const;

signals:
    void clearBoss(QString name, QString difficult);
    void clearBossCancel(QString name, QString difficult);

private:
    Ui::BossWidget *ui;
    Boss bossData;

    class ButtonContainer {
    private:
        SellasButton *difficultButton;
        SellasButton *cancelButton;
        QList<QString> clearShare;
    public:
        ButtonContainer(SellasButton *difficultButton, SellasButton *cancelButton, QList<QString> clearShare):
            difficultButton(difficultButton), cancelButton(cancelButton), clearShare(clearShare){}

        SellasButton *getDifficultButton() const;
        SellasButton *getCancelButton() const;
        QList<QString> getClearShare() const;
    };

    QMap<QString, ButtonContainer> difficultButtonMap;
};

#endif // BOSSWIDGET_H
