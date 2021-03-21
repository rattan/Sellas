#include "datedatasource.h"

#include <QDate>
#include <QTime>

DateDataSource::DateDataSource()
{

}

QDateTime DateDataSource::getDailyInitializedDateTime(QDateTime currentTime)
{
    QDateTime dailyInitialized = currentTime;
    dailyInitialized.setTime(QTime(0,0,0));
    return dailyInitialized;
}

QDateTime DateDataSource::getWeeklyInitializedDateTime(QDateTime currentTime)
{
    QDateTime weeklyInitialized = currentTime;
    int fromTargetDays = (weeklyInitialized.date().dayOfWeek() - INITIALIZE_DAY + WEEK_DATE) % WEEK_DATE;
    weeklyInitialized = weeklyInitialized.addDays(-fromTargetDays);
    weeklyInitialized.setTime(QTime(0,0,0));
    return weeklyInitialized;
}

QDateTime DateDataSource::getMonthlyInitializedDateTime(QDateTime currentTime)
{
    QDateTime monthlyInitialized = currentTime;
    monthlyInitialized = monthlyInitialized.addDays(-monthlyInitialized.date().day());
    monthlyInitialized.setTime(QTime(0,0,0));
    return monthlyInitialized;
}
