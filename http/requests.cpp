#include "requests.h"

#include <QtNetwork>
#include <QThread>

Requests::Requests()
{
    connect(&manager, &QNetworkAccessManager::finished, [&](QNetworkReply *reply){eventLoop.quit();});
    #if QT_CONFIG(ssl)
    connect(&manager, &QNetworkAccessManager::sslErrors, this, &Requests::sslErrors);
    #endif
}

void Requests::get(QNetworkRequest request, std::function<void (QNetworkReply *)> replyCallBack)
{
    QNetworkReply *reply = manager.get(request);
    connect(reply, &QNetworkReply::finished, [replyCallBack, reply](){
        replyCallBack(reply);
    });
}

QNetworkReply *Requests::get(QNetworkRequest request)
{
    QNetworkReply *reply = manager.get(request);
    eventLoop.exec();
    return reply;
}

#if QT_CONFIG(ssl)
//! [sslerrors-2]
void Requests::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    QString errorString;
    for (const QSslError &error : errors) {
        if (!errorString.isEmpty())
            errorString += '\n';
        errorString += error.errorString();
    }
    qDebug()<<"ssl error "<<errorString;
    reply->ignoreSslErrors();
}
//! [sslerrors-2]
#endif
