#include "sellas.h"
#include "sellasparser.h"

#include <QJsonDocument>

SellasParser::SellasParser(QFile file)
{
    this->file.setFileName(file.fileName());
}

Sellas SellasParser::parse()
{
    this->file.open(QIODevice::ReadOnly|QIODevice::Text);
    QString jsonString = file.readAll();
    this->file.close();
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    return Sellas(doc.object());
}
