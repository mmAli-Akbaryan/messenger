
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{//#91A8D0
    ui->setupUi(this);
    this->setStyleSheet("background-color:white");
    this->
    manager = new QNetworkAccessManager();
 //   connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::replyFinished);
    loop = new QEventLoop();
    request = new QNetworkRequest();
    token = Q_NULLPTR;

    connect(manager, SIGNAL(finished(QNetworkReply*)), loop, SLOT(quit()));

    connect(&logout, SIGNAL(logoutCancelled()), this, SLOT(onLogoutCancelled()));
    connect(&logout, SIGNAL(logoutCompleted()), this, SLOT(onLogoutCompleted()));
    //ui->mainToolBar->close();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}


void MainWindow::logOut()
{
    logout.show();
}

void MainWindow::onLogoutCancelled()
{

    this->show();
    logout.close();
    this->hide();
}
void MainWindow::onLogoutCompleted()
{
    logout.close();
  //  this->close();
}






/*
void MainWindow::replyFinished(QNetworkReply* reply)
{
    this->reply = reply;
    QString message = useJson(reply, "message");
    QMessageBox mm;
    mm.setText(message);
   // mm.exec();
}
*/
/*
QString MainWindow::useNetwork(QNetworkRequest * request, QString key)
{
    reply = NULL;
    manager->get(*request);
    //while(!reply){}
    return useJson(reply, key);
}
*/

QJsonObject *MainWindow::useJson(QNetworkReply* reply)
{
    QByteArray barr = reply->readAll();
    QString str = QString(barr);
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject *obj =new QJsonObject();
    *obj = doc.object();
    return obj;
}


void MainWindow::on_Login_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);}
void MainWindow::on_signUp_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);}
void MainWindow::on_cancel_pushButton_signUp_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);}
void MainWindow::on_cancel_pushButton_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_signUp_pushButton_clicked()
{
    if(ui->userName_lineEdit_signUp != NULL && ui->password_lineEdit_login != NULL){
        QString url("http://api.softserver.org:1104/signup?username=" + ui->userName_lineEdit_signUp->text()
                 +"&password=" + ui->password_lineEdit_signUp->text());
        if(ui->firs_lineEdit->text() != NULL)
            url += ("&firstname=" + ui->firs_lineEdit->text());
        if(ui->last_lineEdit->text() != NULL)
            url += ("&lastname=" + ui->last_lineEdit->text());
        request->setUrl(QUrl(url));
        //QString message = useNetwork(request, "message");
        reply = manager->get(*request);
        loop->exec();

        QJsonObject job = *useJson(reply);
        QMessageBox mm;
        mm.setText(job["message"].toString());
        mm.exec();
    }

    else if(ui->userName_lineEdit_signUp == NULL && ui->password_lineEdit_login != NULL){
        QMessageBox mm;
        mm.setText("please choose a username");
        mm.exec();
    }

    else if(ui->userName_lineEdit_signUp != NULL && ui->password_lineEdit_login == NULL){
        QMessageBox mm;
        mm.setText("please choose a password");
        mm.exec();
    }

    else if(ui->userName_lineEdit_signUp == NULL && ui->password_lineEdit_login == NULL){
        QMessageBox mm;
        mm.setText("please choose a username and password");
        mm.exec();
    }

}

void MainWindow::on_login_pushButton_clicked()
{
    if(ui->userName_lineEdit_login != NULL && ui->password_lineEdit_login !=NULL){
        QString url("http://api.softserver.org:1104/login?username=" + ui->userName_lineEdit_login->text()
                + "&password=" + ui->password_lineEdit_login->text());
        request->setUrl(QUrl(url));
        reply = manager->get(*request);
        loop->exec();

        QJsonObject job = *useJson(reply);

        if(job["message"] == "You are already logged in!"){         //logout and login to recieve token
            url = ("http://api.softserver.org:1104/logout?username=" + ui->userName_lineEdit_login->text()
                   + "&password=" + ui->password_lineEdit_login->text());
            request->setUrl(QUrl(url));
            manager->get(*request);
            loop->exec();
            url = ("http://api.softserver.org:1104/login?username=" + ui->userName_lineEdit_login->text()
                   + "&password=" + ui->password_lineEdit_login->text());
            request->setUrl(QUrl(url));
            reply = manager->get(*request);
            loop->exec();
            job = *useJson(reply);
        }

        QMessageBox mm;
        mm.setText(job["message"].toString());
        mm.exec();

        if(job["code"] == "200"){
            //this->hide();
            token = job["token"].toString();
            chats = new Chats(token, manager,this);
            chats->show();
            //chats->exec();

            connect(chats, &Chats::doLogOut, this, &MainWindow::logOut);
            this->setVisible(0);
            //this->hide();
        }
    }

    else if(ui->userName_lineEdit_login == NULL && ui->password_lineEdit_login != NULL){
        QMessageBox mm;
        mm.setText("please enter your username");
        mm.exec();
    }

    else if(ui->userName_lineEdit_login != NULL && ui->password_lineEdit_login == NULL){
        QMessageBox mm;
        mm.setText("please enter your password");
        mm.exec();
    }

    else if(ui->userName_lineEdit_login == NULL && ui->password_lineEdit_login == NULL){
        QMessageBox mm;
        mm.setText("please enter your username and password");
        mm.exec();
    }
}
