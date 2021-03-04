#include "character.h"

Character::Character(QString name, QString server, int level, unsigned long long exp, int popularity, QString job, QString jobDetail, QString guild, QPixmap avatar, QString avatarUrl):
    name(name), server(server), level(level), exp(exp), popularity(popularity), job(job), jobDetail(jobDetail), guild(guild), avatar(avatar), avatarUrl(avatarUrl)
{
    if(level < 1) level = 1;
    if(level > 300) level = 300;
    if(exp < 0) exp = 0;

}

Character::Character(const QSqlQuery query)
{
    this->name = query.value("name").toString();
    this->server = query.value("server").toString();
    this->level = query.value("level").toInt();
    this->exp = query.value("exp").toULongLong();
    this->popularity = query.value("popularity").toInt();
    this->job = query.value("job").toString();
    this->jobDetail = query.value("job_detail").toString();
    this->guild = query.value("guild").toString();
    this->avatarUrl = query.value("avatar_url").toString();
    QByteArray avatarArray = query.value("avatar").toByteArray();
    this->avatar.loadFromData(avatarArray, "png");
}

//const Character Character::CAHRACTER_NODATA = Character("", "", 0, 0, 0, "", "", "", QPixmap(0, 0), "");

QString Character::getName() const
{
    return name;
}

QString Character::getServer() const
{
    return server;
}

int Character::getLevel() const
{
    return level;
}

unsigned long long Character::getExp() const
{
    return exp;
}

int Character::getPopularity() const
{
    return popularity;
}

QString Character::getJob() const
{
    return job;
}

QString Character::getJobDetail() const
{
    return jobDetail;
}

QString Character::getGuild() const
{
    return guild;
}

QPixmap Character::getAvatar() const
{
    return avatar;
}

QString Character::getAvatarUrl() const
{
    return avatarUrl;
}

QString Character::toString() const
{
    QString str("name=%1, server=%2, level=%3, exp=%4, popularity=%5, job=%6, job_detail=%7, guild=%8, avatar_url=%9");
    return str.arg(name).arg(server).arg(level).arg(exp).arg(popularity).arg(job).arg(jobDetail).arg(guild).arg(avatarUrl);
}

Character::Character()
{

}
