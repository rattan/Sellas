#ifndef DATEDATASOURCE_H
#define DATEDATASOURCE_H

#include <QDateTime>

#define MONDAY 1
#define TUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6
#define SUNDAY 7

#define WEEK_DATE 7
#define INITIALIZE_DAY THURSDAY

class DateDataSource
{
public:
    DateDataSource();

    QDateTime getDailyInitializedDateTime(QDateTime currentTime = QDateTime::currentDateTime());
    QDateTime getWeeklyInitializedDateTime(QDateTime currentTime = QDateTime::currentDateTime());
    QDateTime getMonthlyInitializedDateTime(QDateTime currentTime = QDateTime::currentDateTime());
private:
};

#endif // DATEDATASOURCE_H
