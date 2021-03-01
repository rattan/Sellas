#ifndef CHARACTER_H
#define CHARACTER_H

#include <QPixmap>
#include <QSqlQuery>
#include <QString>



class Character
{
public:
    Character(QString name, QString server, int level, unsigned long long exp, int popularity, QString job, QString jobDetail, QString guild, QString avatarCache, QString avatarWeb);
    Character(const QSqlQuery query);
    QString getName() const;
    QString getServer() const;
    int getLevel() const;
    unsigned long long getExp() const;
    int getPopularity() const;
    QString getJob() const;
    QString getJobDetail() const;
    QString getGuild() const;
    QPixmap getAvatar();
    QString getAvatarCache() const;
    QString getAvatarWeb() const;

    QString toString() const;

private:
    QString name;
    QString server;
    int level;
    unsigned long long exp;
    int popularity;
    QString job;
    QString jobDetail;
    QString guild;
    QString avatarCache;
    QString avatarWeb;
    QPixmap *avatar;
};

#endif // CHARACTER_H
