#include "logout.h"
#include "ui_logout.h"
#include <QMessageBox>

Logout::Logout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logout)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:white");
    manager = new QNetworkAccessManager();
    request = new QNetworkRequest();
}

Logout::~Logout()
{
    delete ui;
}


void Logout::on_pushButton_cancel_logout_clicked()
{
    //this->close();
    emit logoutCancelled();
}

void Logout::on_pushButton_logout_clicked()
{
    if(ui->userName_lineEdit_logout != NULL && ui->password_lineEdit_logout != NULL){
        QString url("http://api.softserver.org:1104/logout?username=" + ui->userName_lineEdit_logout->text()
                    + "&password=" + ui->password_lineEdit_logout->text());
        request->setUrl(QUrl(url));
        reply = manager->get(*request);
        QByteArray barr = reply->readAll();
        QString str = QString(barr);
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject job = doc.object();
        QMessageBox mm;
        mm.setText("hello" + job["message"].toString());
        mm.exec();
        if(job["code"].toString() == "200"){
            emit logoutCompleted();
        }
    }

    else if(ui->userName_lineEdit_logout == NULL && ui->password_lineEdit_logout != NULL){
        QMessageBox mm;
        mm.setText("please enter your UserName");
        mm.exec();
    }

    else if(ui->userName_lineEdit_logout != NULL && ui->password_lineEdit_logout == NULL){
        QMessageBox mm;
        mm.setText("please enter your Password");
        mm.exec();
    }

    else if(ui->userName_lineEdit_logout == NULL && ui->password_lineEdit_logout == NULL){
        QMessageBox mm;
        mm.setText("please enter your UserName and Password");
        mm.exec();
    }
}
















