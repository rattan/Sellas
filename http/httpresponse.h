#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QString>
#include <QStringList>

class HttpResponse
{
private:
    int status;
    QString version;
    QStringList header;
    QStringList cookie;
    QByteArray body;
public:
    HttpResponse();
};

#endif // HTTPRESPONSE_H
