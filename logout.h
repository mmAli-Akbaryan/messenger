#ifndef LOGOUT_H
#define LOGOUT_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class Logout;
}

class Logout : public QDialog
{
    Q_OBJECT

public:
    explicit Logout(QWidget *parent = 0);
    ~Logout();

signals:
    void logoutCancelled();
    void logoutCompleted();

private slots:

    void on_pushButton_cancel_logout_clicked();

    void on_pushButton_logout_clicked();

private:
    Ui::Logout *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest * request;
    QNetworkReply *reply;
};

#endif // LOGOUT_H
