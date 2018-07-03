#include "chats.h"
#include "ui_chats.h"
#include <QMessageBox>

Chats::Chats(QString token, QNetworkAccessManager *manager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chats)
{
    ui->setupUi(this);
    this->showMaximized();
    this->token = token;
    this->manager = manager;
    updater = new Updater(token, manager);
    connect(updater, &Updater::pvListChanged, this, &Chats::onPvListChanged);
    connect(updater, &Updater::gpListChanged, this, &Chats::onGpListChanged);
    connect(updater, &Updater::chListChanged, this, &Chats::onChListChanged);
    connect(updater, &Updater::openPvChanged, this, &Chats::onOpenPvChanged);
    connect(updater, &Updater::openGpChanged, this, &Chats::onOpenGpChanged);
    connect(updater, &Updater::openChChanged, this, &Chats::onOpenChChanged);

    connect(this, &Chats::currentPV, updater, &Updater::onCurrentPV);
    connect(this, &Chats::currentGP, updater, &Updater::onCurrentGP);
    connect(this, &Chats::currentCH, updater, &Updater::onCurrentCH);

  //  connect(&logout, SIGNAL(logoutCancelled()), this, SLOT(onLogoutCancelled()));
    //connect(&logout, SIGNAL(logoutCompleted()), this, SLOT(onLogoutCompleted()));

    ui->actionhello_3->setShortcut(QKeySequence("hello key"));

    updater->start();
}

Chats::~Chats()
{
    delete updater;
    delete ui;
}



void Chats::onPvListChanged(const QJsonObject &json)
{
    QStringList list = (json["message"].toString().split('-'));
    QString str = list[1];
    int num = str.toInt();

    ui->listWidget_PV->clear();
    for(int i = 0; i < num; i++){
        ui->listWidget_PV->addItem(json["block " + i].toObject()["user_name"].toString());             //check user_name
    }
    PVList = json;
}

void Chats::onGpListChanged(const QJsonObject &json)
{
    qDebug() <<"in gplistChanged slot";
    QStringList list = (json["message"].toString().split('-'));
    QString str = list[1];
    int num = str.toInt();

    ui->listWidget_GP->clear();
    for(int i = 0; i < num; i++){
        ui->listWidget_GP->addItem(json["block " + QString::number(i)].toObject()["group_name"].toString());

    }
    GPList = json;
}

void Chats::onChListChanged(const QJsonObject &json)
{
    qDebug() <<"in chnl listChanged slot";
    QStringList list = (json["message"].toString().split('-'));
    QString str = list[1];
    int num = str.toInt();

    ui->listWidget_chnl->clear();
    for(int i = 0; i < num; i++){
        ui->listWidget_chnl->addItem(json["block " + i].toObject()["channel_name"].toString());
    }
    CHList = json;
}

void Chats::onOpenPvChanged(const QJsonObject &json)
{
    QStringList list = (json["message"].toString().split('-'));
    QString str = list[1];
    int num = str.toInt();

    ui->textBrowser_PV->clear();
    for(int i = 0; i<num; i++){
        ui->textBrowser_PV->append(titleStyle(QJsonObject(json["block " + i].toObject())["src"].toString())
                + QJsonObject(json["block " + i].toObject())["body"].toString() + '\n');
    }
}

void Chats::onOpenGpChanged(const QJsonObject &json)
{
    QStringList list = (json["message"].toString().split('-'));
    QString str = list[1];
    int num = str.toInt();

    ui->textBrowser_GP->clear();
    for(int i = 0; i<num; i++){
        ui->textBrowser_GP->append(titleStyle(QJsonObject(json["block " + i].toObject())["src"].toString())
                + QJsonObject(json["block " + i].toObject())["body"].toString() + '\n');
    }
}

void Chats::onOpenChChanged(const QJsonObject &json)
{
    QStringList list = (json["message"].toString().split('-'));
    QString str = list[1];
    int num = str.toInt();

    ui->textBrowser_chnl->clear();
    for(int i = 0; i<num; i++){
        ui->textBrowser_chnl->append(titleStyle(QJsonObject(json["block " + i].toObject())["src"].toString())
                + QJsonObject(json["block " + i].toObject())["body"].toString() + '\n');
    }
}


QString Chats::titleStyle(const QString &text)
{
    return "<span style=\"font-size:20pt; font-weight:bold \" >" + text + ": " + "</span>";
}

void Chats::on_logout_pushButton_clicked()
{
   // logout.exec();
    emit doLogOut();
}
/*
void Chats::onLogoutCancelled()
{
  //  logout.close();
}
void Chats::onLogoutCompleted()
{
  //  logout.close();
  //  this->close();
}
*/

void Chats::on_listWidget_PV_itemSelectionChanged()
{
    emit currentPV(QJsonObject(PVList["block " + ui->listWidget_PV->currentRow()].toObject())["user_name"].toString());            //check user_name
}

void Chats::on_listWidget_GP_itemSelectionChanged()
{
    emit currentGP(QJsonObject(GPList["block " + ui->listWidget_GP->currentRow()].toObject())["group_name"].toString());
}

void Chats::on_listWidget_chnl_itemSelectionChanged()
{
    emit currentCH(QJsonObject(CHList["block " + ui->listWidget_chnl->currentRow()].toObject())["channel_name"].toString());
}





















