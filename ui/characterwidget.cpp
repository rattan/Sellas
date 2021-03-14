#include "characterwidget.h"
#include "ui_characterwidget.h"

CharacterWidget::CharacterWidget(const Character &character, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterWidget),
    characterData(character)
{
    ui->setupUi(this);
    this->ui->characterIamgeWidget->setPixmap(character.getAvatar());
    this->ui->nameLabel->setText(character.getName());
}

CharacterWidget::~CharacterWidget()
{
    delete ui;
}
