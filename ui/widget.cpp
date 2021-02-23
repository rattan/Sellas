#include "widget.h"
#include "ui_widget.h"

#include <QtNetwork>
#include <QUrl>

#include <ui/bosslistwidgetitem.h>

#include <model/sellas.h>
#include <model/sellasparser.h>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
SellasParser parser(QFile("sellas.json"));
    Sellas sellas = parser.parse();
    for(auto boss: sellas.getBossList()) {
        QListWidgetItem *it = new QListWidgetItem(ui->listWidget_2);
        BossListWidgetItem *item = new BossListWidgetItem(boss);
        it->setSizeHint(item->sizeHint());
        ui->listWidget_2->setItemWidget(it, item);
        ui->listWidget_2->addItem(it);
    }
    for(int i=0;i<5;++i) {

        ui->listWidget->addItem(QString::number(i));
    }
    connect(ui->listWidget, &QListWidget::itemClicked, this, &Widget::on_character_list_item_clicked);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{


    req.get(QNetworkRequest(QUrl("https://www.google.com")), [](QNetworkReply* reply){qDebug()<<reply->readAll();});
    qDebug()<<"END";
}

void Widget::on_character_list_item_clicked(QListWidgetItem *item)
{
    qDebug()<<item->text();
}
