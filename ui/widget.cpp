#include "widget.h"
#include "ui_widget.h"

#include <QtNetwork>
#include <QUrl>
#include <QScrollBar>
#include <ui/bosswidget.h>

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
//    qDebug()<<sellas.toString();
    ui->bossListWidget->horizontalScrollBar()->setSingleStep(243);
    for(auto boss: sellas.getBossList()) {
        QListWidgetItem *it = new QListWidgetItem(ui->bossListWidget);
        ui->bossListWidget->addItem(it);
        BossWidget *item = new BossWidget(boss);
        it->setSizeHint(item->sizeHint());
        ui->bossListWidget->setItemWidget(it, item);
    }
    for(int i=0;i<5;++i) {

        ui->characterListWidget->addItem(QString::number(i));
    }
    connect(ui->characterListWidget, &QListWidget::itemClicked, this, &Widget::on_character_list_item_clicked);
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
