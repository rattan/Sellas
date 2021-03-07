#include "sellas.h"

#include <QJsonArray>
#include <QJsonDocument>

QList<Boss> Sellas::getBossList() const
{
    return bossList;
}

QString Sellas::getDatabase() const
{
    return database;
}

QString Sellas::getVersion() const
{
    return version;
}

QString Sellas::getName() const
{
    return name;
}

QList<Server> Sellas::getServerList() const
{
    return serverList;
}

QList<QPair<QString, QList<QString> > > Sellas::getJobList() const
{
    return jobList;
}

void Sellas::initFromJson(QJsonObject json)
{
    this->name = json.value("name").toString();
    this->version = json.value("version").toString();
    this->database = json.value("database").toString();

    bossList.clear();
    for(auto bossObject: json.value("boss").toArray()) {
        bossList.append(Boss(bossObject.toObject()));
    }

    serverList.clear();
    for(auto serverObject: json.value("server").toArray()) {
        Server server(serverObject.toObject());
        serverList.append(server);
    }
    for(auto job: json.value("job").toArray()) {
        auto jobObj = job.toObject();
        QList<QString> jobDetailList;
        for(auto jobDetail: jobObj.value("job_detail").toArray()) {
            jobDetailList.append(jobDetail.toString());
        }
        this->jobList.append(QPair<QString, QList<QString>>(jobObj.value("name").toString(), jobDetailList));
    }
}

QJsonObject Sellas::toJson() const
{
    QJsonObject sellasObject;
    sellasObject.insert("name", QJsonValue(this->name));
    sellasObject.insert("version", QJsonValue(this->version));
    sellasObject.insert("database", QJsonValue(this->database));
    QJsonArray bossArray;
    for(auto boss: this->bossList) {
        bossArray.append(boss.toJson());
    }
    sellasObject.insert("boss", bossArray);
    QJsonArray serverArray;
    for(auto server: this->serverList) {
        serverArray.append(server.toJson());
    }
    sellasObject.insert("server", serverArray);
    QJsonArray jobArray;
    for(auto job: this->jobList) {
        QJsonObject jobObject;
        jobObject.insert("name", job.first);
        QJsonArray jobDetailArray;
        for(auto jobDetail: job.second) {
            jobDetailArray.append(jobDetail);
        }
        jobObject.insert("job_detail", jobDetailArray);
    }
    sellasObject.insert("job", jobArray);

    return sellasObject;
}
