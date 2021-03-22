#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include <QTimer>

class NotificationService: public QObject
{
Q_OBJECT
public:
    NotificationService();
    void start();
    void stop();

private slots:
    void timeOut();
private:
    QTimer timer;


};

#endif // NOTIFICATIONSERVICE_H
