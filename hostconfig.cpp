#include "hostconfig.h"
#include "ui_hostconfig.h"
#include "qfiledialog.h"
#include "QtNetwork/qhostinfo.h"
#include "QtNetwork/qhostaddress.h"
#include "QtNetwork/qnetworkinterface.h"
#include "QtNetwork"

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
        root_path = dir;
    }else
    {
    }

}

void HostConfig::on_pushButton_2_clicked()
{
    //Getting local host name
    QString localhostname =  QHostInfo::localHostName();
       QString localhostIP;
       QList<QHostAddress> hostList = QHostInfo::fromName(localhostname).addresses();
       foreach (const QHostAddress& address, hostList) {
           if (address.protocol() == QAbstractSocket::IPv4Protocol) {
                localhostIP = address.toString();
           }
       }


       //Get MAC address
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

         //Ping extern website API to get public ipv6
         QNetworkAccessManager manager;
         QNetworkReply *response = manager.get(QNetworkRequest(QUrl("http://api.ipify.org")));
         QEventLoop event;
         connect(response,SIGNAL(finished()),&event,SLOT(quit()));
         event.exec();
         QString ipv6 = response->readAll();


    //Apply value
    ui->ipv4->setText(localhostIP);
    ui->hostname->setText(localhostname);
    ui->mac->setText(localMacAddress);
    ui->subnet->setText(localNetmask);
    ui->ipv6->setText(ipv6);
}

//writing configuration file
void HostConfig::on_pushButton_3_clicked()
{
    //Empy TextEdit
    QTextEdit *tx = new QTextEdit(this);


    //login
    QString login = root_path;
    login.append("/conf/login_athena.conf");

    QFile inputFile(login);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();

          if(line.contains(tr("login_port:")))
          {
             tx->append(QString("login_port: %1").arg(ui->spinBox->value()));
              continue;
          }

          tx->append(line);

       }
       inputFile.close();
    }



    //Char
    tx->clear();
    QString chars = root_path;
    chars.append("/conf/char_athena.conf");

    QFile inputFile2(chars);
    if(inputFile2.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile2);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            if(line.contains(tr("login_ip:")))
            {
                tx->append(QString("login_ip: %1").arg(ui->ipv6->text()));
                continue;
            }
            if(line.contains(tr("login_port:")))
            {
                tx->append(QString("login_port: %1").arg(ui->spinBox->value()));
                continue;
            }
            if(line.contains(tr("char_ip:")))
            {
                tx->append(QString("char_ip: %1").arg(ui->ipv6->text()));
                continue;
            }
            if(line.contains(tr("char_port:")))
            {
                tx->append(QString("char_port: %1").arg(ui->spinBox_2->value()));
                continue;
            }
            if(line.contains(tr("server_name:")))
            {
                tx->append(QString("server_name: %1").arg(ui->servername->text()));
            }

            tx->append(line);
        }

        ui->textEdit->setText(tx->toPlainText());
    }

}
