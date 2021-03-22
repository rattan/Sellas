
#include <QApplication>

#include <ui/widget.h>

#include <service/notificationservice.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    NotificationService noti;
    noti.start();
    return a.exec();
}
