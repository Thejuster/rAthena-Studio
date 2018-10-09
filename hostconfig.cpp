#include "hostconfig.h"
#include "ui_hostconfig.h"
#include "qfiledialog.h"
#include "QtNetwork/qhostinfo.h"
#include "QtNetwork/qhostaddress.h"
#include "QtNetwork/qnetworkinterface.h"

HostConfig::HostConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HostConfig)
{
    ui->setupUi(this);
}

HostConfig::~HostConfig()
{
    delete ui;
}

void HostConfig::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,tr("Select rAthena Folder"),"/home",
                                                    QFileDialog::ShowDirsOnly |
                                                    QFileDialog::DontResolveSymlinks);

    if(!dir.isEmpty())
    {
        ui->lineEdit->setText(dir);
    }else
    {
    }

}

void HostConfig::on_pushButton_2_clicked()
{
    QString localhostname =  QHostInfo::localHostName();
       QString localhostIP;
       QList<QHostAddress> hostList = QHostInfo::fromName(localhostname).addresses();
       foreach (const QHostAddress& address, hostList) {
           if (address.protocol() == QAbstractSocket::IPv4Protocol) {
                localhostIP = address.toString();
           }
       }


       QString localMacAddress;
         QString localNetmask;
         foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces()) {
             foreach (const QNetworkAddressEntry& entry, networkInterface.addressEntries()) {
                 if (entry.ip().toString() == localhostIP) {
                     localMacAddress = networkInterface.hardwareAddress();
                     localNetmask = entry.netmask().toString();
                     break;
                 }
             }
         }


    ui->lineEdit_2->setText(localhostIP);
    ui->lineEdit_3->setText(localhostname);
    ui->lineEdit_4->setText(localMacAddress);
    ui->lineEdit_5->setText(localNetmask);
}

void HostConfig::on_pushButton_3_clicked()
{

}
