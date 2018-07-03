#include "updater.h"


Updater::Updater(const QString &token, QNetworkAccessManager *manager)
{
    this->token = token;
    this->manager = manager;
    loop = new QEventLoop();
    request = new QNetworkRequest();
    connect(manager, &QNetworkAccessManager::finished, loop, &QEventLoop::quit);
    currentPV = ""; currentGP = ""; currentCH = "";
}

Updater::~Updater()
{
    delete manager;
    delete loop;
    delete request;
}


void Updater::run()
{
    qDebug() <<"hello i'm in run!!!";
    QString url;
    for(; 1; this->sleep(5)){

        //list of pv
        url = ("http://api.softserver.org:1104/getuserlist?token=" + token);
        request->setUrl(QUrl(url));
        reply = manager->get(*request);
        loop->exec();
        emit pvListChanged(* useJson(reply));

        //list of groups
        url = ("http://api.softserver.org:1104/getgrouplist?token=" + token);
        request->setUrl(QUrl(url));
        reply = manager->get(*request);
        loop->exec();
        emit gpListChanged(* useJson(reply));
        qDebug() <<"gpListChanged emited";

        //list of channels
        url = ("http://api.softserver.org:1104/getchannellist?token=" + token);
        request->setUrl(QUrl(url));
        reply = manager->get(*request);
        loop->exec();
        emit chListChanged(* useJson(reply));

        //current PV
        if(currentPV != ""){
            url = ("http://api.softserver.org:1104/getuserchats?token=" + token + "&dst=" + currentPV);
            request->setUrl(QUrl(url));
            reply = manager->get(*request);
            loop->exec();
            emit openPvChanged(* useJson(reply));
        }

        //current Group
        if(currentGP != ""){
            url = ("http://api.softserver.org:1104/getgroupchats?token=" + token + "&dst=" + currentGP);
            request->setUrl(QUrl(url));
            reply = manager->get(*request);
            loop->exec();
            emit openGpChanged(* useJson(reply));
        }

        //current Channel
        if(currentCH != ""){
            url = ("http://api.softserver.org:1104/getchannelchats?token=" + token + "&dst=" + currentCH);
            request->setUrl(QUrl(url));
            reply = manager->get(*request);
            loop->exec();
            emit openChChanged(* useJson(reply));
        }

    }//end for
}


void Updater::onCurrentPV(QString userName)
{
    currentPV = userName;
}
void Updater::onCurrentGP(QString userName)
{
    currentGP = userName;
}
void Updater::onCurrentCH(QString userName)
{
    currentCH = userName;
}



QJsonObject *Updater::useJson(QNetworkReply* reply)
{
    QByteArray barr = reply->readAll();
    QString str = QString(barr);
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject *obj =new QJsonObject();
    *obj = doc.object();
    return obj;
}
