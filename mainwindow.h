#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QEventLoop>
#include "chats.h"
#include "logout.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

     QJsonObject *useJson(QNetworkReply* reply);

    // static QString useNetwork(QNetworkRequest * request, QString key);


public slots:
     void logOut();
     void onLogoutCancelled();
     void onLogoutCompleted();

private slots:
    void on_Login_button_clicked();

    void on_signUp_button_clicked();

    void on_cancel_pushButton_signUp_clicked();

    void on_cancel_pushButton_login_clicked();

    void on_signUp_pushButton_clicked();

   // void replyFinished(QNetworkReply * reply);

    void on_login_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Chats *chats;
    QString token;
    QEventLoop *loop;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    Logout logout;
};

#endif // MAINWINDOW_H
