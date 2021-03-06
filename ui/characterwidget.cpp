#include "characterwidget.h"
#include "ui_characterwidget.h"

CharacterWidget::CharacterWidget(Character character, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterWidget),
    characterData(character)
{
    ui->setupUi(this);
    this->ui->characterIamgeWidget->setPixmap(characterData.getAvatar());
    this->ui->nameLabel->setText(characterData.getName());
}

CharacterWidget::~CharacterWidget()
{
    delete ui;
}

const Character &CharacterWidget::getCharacterData() const
{
    return characterData;
}
