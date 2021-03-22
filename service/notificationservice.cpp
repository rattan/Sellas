#include "notificationservice.h"

#include <QDateTime>
#include <QSystemTrayIcon>

NotificationService::NotificationService()
{
    connect(&timer, &QTimer::timeout, this, &NotificationService::timeOut);
}

void NotificationService::start()
{
    timer.start();
}

void NotificationService::stop()
{
    timer.stop();
}

void NotificationService::timeOut()
{
    QDateTime dt = QDateTime::currentDateTime();
    qDebug()<<dt;
    QTime time = dt.time();
    timer.setInterval(60000 - (time.second() * 1000 + time.msec()));
}
