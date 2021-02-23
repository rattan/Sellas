#ifndef SELLASPARSER_H
#define SELLASPARSER_H

#include "sellas.h"

#include <QFile>
#include <QString>



class SellasParser
{
private:
QFile file;

public:
//    SellasParser(QJsonObject jsonString);
//    SellasParser(QString jsonString);
    SellasParser(QFile file);
//    SellasParser(QUrl path);

    Sellas parse();
};

#endif // SELLASPARSER_H
