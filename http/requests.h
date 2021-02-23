#ifndef REQUESTS_H
#define REQUESTS_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QThread>
#include <QEventLoop>

#include <functional>

class Requests: public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager manager;
    QEventLoop eventLoop;

private slots:
#if QT_CONFIG(ssl)
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
#endif

public:
    Requests();
    void get(QNetworkRequest request, std::function<void(QNetworkReply*)> replyCallBack);
    QNetworkReply *get(QNetworkRequest request);
};

#endif // REQUESTS_H

