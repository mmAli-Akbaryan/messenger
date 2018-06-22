#ifndef CHATS_H
#define CHATS_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "updater.h"
#include "logout.h"
#include <QEventLoop>

namespace Ui {
class Chats;
}

class Chats : public QDialog
{
    Q_OBJECT

public:
    explicit Chats(QString token, QWidget *parent = 0);
    ~Chats();
    QString titleStyle(const QString &text);

signals:
    void currentPV(QString);
    void currentGP(QString);
    void currentCH(QString);

    void doLogOut();

public slots:
    void onPvListChanged(const QJsonObject &json);
    void onGpListChanged(const QJsonObject &json);
    void onChListChanged(const QJsonObject &json);
    void onOpenPvChanged(const QJsonObject &json);
    void onOpenGpChanged(const QJsonObject &json);
    void onOpenChChanged(const QJsonObject &json);

  //  void onLogoutCancelled();
    //void onLogoutCompleted();

private slots:
    void on_logout_pushButton_clicked();

    void on_listWidget_PV_itemSelectionChanged();

    void on_listWidget_GP_itemSelectionChanged();

    void on_listWidget_chnl_itemSelectionChanged();

private:
    Ui::Chats *ui;
    QString token;
    Updater *updater;
   // Logout logout;
    QJsonObject PVList;     //used for finding username of clicked item
    QJsonObject GPList;     //used for finding username of clicked item
    QJsonObject CHList;     //used for finding username of clicked item
};

#endif // CHATS_H
