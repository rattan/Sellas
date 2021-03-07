#include "widget.h"
#include "ui_widget.h"

#include <QtNetwork>
#include <QUrl>
#include <QScrollBar>
#include <QDialog>
#include <ui/characteradddialog.h>
#include <ui/bosswidget.h>

#include <ui/bosslistwidgetitem.h>

#include <model/sellas.h>
#include <model/sellasparser.h>


Widget::Widget(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Widget),
    sellas(SellasParser(QFile(":/data/data/sellas.json")).parse())
{
    ui->setupUi(this);
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
    CharacterAddDialog characterAddDialog(sellas);

    if (characterAddDialog.exec() == QDialog::Accepted) {
        qDebug()<<"Accepted";
        characterDataSource.insertCharacter(characterAddDialog.getCharacter());
    }
}

void Widget::on_character_list_item_clicked(QListWidgetItem *item)
{
    qDebug()<<item->text();
}
