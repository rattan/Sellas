#include "widget.h"
#include "ui_widget.h"
#include "characterwidget.h"

#include <QtNetwork>
#include <QUrl>
#include <QScrollBar>
#include <QDialog>
#include <ui_characterwidget.h>
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

    initializeUi();
    initializeLoadData();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initializeUi()
{
    ui->bossListWidget->horizontalScrollBar()->setSingleStep(243);
    for(auto boss: sellas.getBossList()) {
        QListWidgetItem *it = new QListWidgetItem(ui->bossListWidget);
        ui->bossListWidget->addItem(it);
        BossWidget *item = new BossWidget(boss);
        it->setSizeHint(item->sizeHint());
        ui->bossListWidget->setItemWidget(it, item);
    }

    connect(ui->characterListWidget, &QListWidget::itemClicked, this, &Widget::on_character_list_item_clicked);
}

void Widget::initializeLoadData()
{
    for(auto character: characterDataSource.getAllCharacters()) {
        QListWidgetItem *it = new QListWidgetItem(ui->characterListWidget);
        ui->characterListWidget->addItem(it);
        CharacterWidget *item = new CharacterWidget(character);
        qDebug()<<item;
        it->setSizeHint(item->sizeHint());
        ui->characterListWidget->setItemWidget(it, item);
    }
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
    CharacterWidget *selectedCharacterWidget = static_cast<CharacterWidget*>(ui->characterListWidget->itemWidget(item));
    qDebug()<<selectedCharacterWidget;

    const Character &character = selectedCharacterWidget->getCharacterData();
    qDebug()<<character.getName();

}
