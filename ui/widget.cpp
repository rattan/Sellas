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

#include <QIcon>
#include <QSystemTrayIcon>


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
    for(auto &boss: sellas.getBossList()) {
        QListWidgetItem *it = new QListWidgetItem(ui->bossListWidget);
        ui->bossListWidget->addItem(it);
        BossWidget *item = new BossWidget(boss);
        it->setSizeHint(item->sizeHint());
        ui->bossListWidget->setItemWidget(it, item);
        connect(item, &BossWidget::clearBoss, [&](QString name, QString difficulty){
            qDebug()<<"clear click";
            CharacterWidget *selectedCharacterWidget = static_cast<CharacterWidget*>(ui->characterListWidget->itemWidget(ui->characterListWidget->currentItem()));
            const Character &character = selectedCharacterWidget->getCharacterData();
            qDebug()<<character.getName();
            this->bossDataSource.clearBossNow(character.getName(), name, difficulty);
        });
        connect(item, &BossWidget::clearBossCancel, [&](QString name, QString difficulty){
            qDebug()<<"clear cancel click";
            CharacterWidget *selectedCharacterWidget = static_cast<CharacterWidget*>(ui->characterListWidget->itemWidget(ui->characterListWidget->currentItem()));
            const Character &character = selectedCharacterWidget->getCharacterData();
            qDebug()<<character.getName();
            this->bossDataSource.clearBossCancel(character.getName(), name, difficulty);
        });
    }

    connect(ui->characterListWidget, &QListWidget::itemClicked, this, &Widget::characterListItemClicked);
}

void Widget::initializeCharacterListWidget()
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

void Widget::initializeBossListWidget()
{
    CharacterWidget *selectedCharacterWidget = static_cast<CharacterWidget*>(ui->characterListWidget->itemWidget(ui->characterListWidget->currentItem()));
    const Character &character = selectedCharacterWidget->getCharacterData();
    int bossCount = ui->bossListWidget->count();
    for(int i=0; i< bossCount; ++i) {
        BossWidget *bossWidget = static_cast<BossWidget*>(ui->bossListWidget->itemWidget(ui->bossListWidget->item(i)));
        bossWidget->clear();
        Boss const &boss = bossWidget->getBossData();
        QList<Boss::Clear> bossClearData = bossDataSource.getBossClear(character.getName(), boss.getName());
        for(auto const &bossClear: bossClearData) {
            bool clear = false;
            QString cycle = boss.findDifficult(bossClear.getDifficult()).getCycle();
            QDateTime clearDateTime = QDateTime::fromSecsSinceEpoch(bossClear.getClearDate());
            if (CYCLE_DAILY == cycle) {
                clear = dateDataSource.getDailyInitializedDateTime() <= clearDateTime;
            } else if (CYCLE_WEEKLY == cycle) {
                clear = dateDataSource.getWeeklyInitializedDateTime() <= clearDateTime;
            } else if (CYCLE_MONTHLY == cycle) {
                clear = dateDataSource.getMonthlyInitializedDateTime() <= clearDateTime;
            }
            bossWidget->setClear(bossClear.getDifficult(), clear);
        }
    }
}

void Widget::initializeLoadData()
{
    initializeCharacterListWidget();

    if(ui->characterListWidget->count() > 0) {
        ui->characterListWidget->setCurrentRow(0);
        initializeBossListWidget();
    }
}

QTimer *timer;
void Widget::on_pushButton_clicked()
{
        CharacterAddDialog characterAddDialog(sellas);

    if (characterAddDialog.exec() == QDialog::Accepted) {
        qDebug()<<"Accepted";
        Character character = characterAddDialog.getCharacter();
        characterDataSource.insertCharacter(character);
        bossDataSource.insertBossesForCharacter(character.getName(), sellas.getBossList());
        QListWidgetItem *it = new QListWidgetItem(ui->characterListWidget);
        ui->characterListWidget->addItem(it);
        CharacterWidget *item = new CharacterWidget(character);
        qDebug()<<item;
        it->setSizeHint(item->sizeHint());
        ui->characterListWidget->setItemWidget(it, item);
    }
}

void Widget::characterListItemClicked(QListWidgetItem *item)
{
    CharacterWidget *selectedCharacterWidget = static_cast<CharacterWidget*>(ui->characterListWidget->itemWidget(item));
    qDebug()<<selectedCharacterWidget;

    const Character &character = selectedCharacterWidget->getCharacterData();
    qDebug()<<character.getName();

    initializeBossListWidget();
}
