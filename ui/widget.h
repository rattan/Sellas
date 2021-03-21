#ifndef WIDGET_H
#define WIDGET_H

#include <QListWidget>
#include <QWidget>

#include <http/requests.h>

#include <model/bossdatasource.h>
#include <model/characterdatasource.h>
#include <model/datedatasource.h>
#include <model/sellas.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void initializeUi();
    void initializeLoadData();

    void on_pushButton_clicked();
    void characterListItemClicked(QListWidgetItem* item);

private:
    Ui::Widget *ui;
    Requests req;
    CharacterDataSource characterDataSource;
    BossDataSource bossDataSource;
    DateDataSource dateDataSource;
    Sellas sellas;
    void initializeCharacterListWidget();
    void initializeBossListWidget();
};
#endif // WIDGET_H
