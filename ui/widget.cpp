#include "widget.h"
#include "ui_widget.h"

#include <QtNetwork>
#include <QUrl>
#include <QScrollBar>
#include <ui/bosslistwidget.h>

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
    ui->listWidget_2->horizontalScrollBar()->setSingleStep(1);
    for(auto boss: sellas.getBossList()) {
        QListWidgetItem *it = new QListWidgetItem(ui->listWidget_2);
        ui->listWidget_2->addItem(it);
        BossListWidget *item = new BossListWidget(boss);
        it->setSizeHint(item->sizeHint());
        ui->listWidget_2->setItemWidget(it, item);
        qDebug()<<boss.getName();
    }
    for(int i=0;i<5;++i) {

        ui->listWidget->addItem(QString::number(i));
    }
    connect(ui->listWidget, &QListWidget::itemClicked, this, &Widget::on_character_list_item_clicked);
    QPushButton bt;
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
