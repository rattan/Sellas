#ifndef CHARACTER_H
#define CHARACTER_H

#include <QPixmap>
#include <QSqlQuery>
#include <QString>



class Character
{
public:
    Character(QString name, QString server, int level, unsigned long long exp, int popularity, QString job, QString jobDetail, QString guild, QPixmap avatar, QString avatarUrl);
    Character(const QSqlQuery query);
    QString getName() const;
    QString getServer() const;
    int getLevel() const;
    unsigned long long getExp() const;
    int getPopularity() const;
    QString getJob() const;
    QString getJobDetail() const;
    QString getGuild() const;
    QPixmap getAvatar() const;
    QString getAvatarUrl() const;
    QString toString() const;

    static const Character& getNoDataCharacter() {
        static const Character c;
        return c;
    }

private:
    Character();
    QString name;
    QString server;
    int level;
    unsigned long long exp;
    int popularity;
    QString job;
    QString jobDetail;
    QString guild;
    QString avatarCache;
    QString avatarUrl;
    QPixmap avatar;
};

#endif // CHARACTER_H
