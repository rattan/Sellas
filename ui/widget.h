#ifndef WIDGET_H
#define WIDGET_H

#include <QListWidget>
#include <QWidget>

#include <http/requests.h>

#include <model/characterdatasource.h>
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
    void on_character_list_item_clicked(QListWidgetItem* item);

private:
    Ui::Widget *ui;
    Requests req;
    CharacterDataSource characterDataSource;
    Sellas sellas;
};
#endif // WIDGET_H
