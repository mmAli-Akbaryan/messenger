#ifndef UPDATER_H
#define UPDATER_H
#include <QThread>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

class Updater : public QThread
{
    Q_OBJECT

public:
    void run();
    Updater(const QString &token, QNetworkAccessManager *manager);
    ~Updater();
    QJsonObject *useJson(QNetworkReply* reply);
signals:
    void pvListChanged(const QJsonObject &json);
    void gpListChanged(const QJsonObject &json);
    void chListChanged(const QJsonObject &json);
    void openPvChanged(const QJsonObject &json);
    void openGpChanged(const QJsonObject &json);
    void openChChanged(const QJsonObject &json);

public slots:
    void onCurrentPV(QString userName);
    void onCurrentGP(QString userName);
    void onCurrentCH(QString userName);


public:
    QString token;
    QNetworkAccessManager *manager;
    QEventLoop *loop;
    QNetworkRequest *request;
    QNetworkReply *reply;

    QString currentPV;
    QString currentGP;
    QString currentCH;
};

#endif // UPDATER_H
