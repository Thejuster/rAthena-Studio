#include "hostconfig.h"
#include "ui_hostconfig.h"
#include "qfiledialog.h"
#include "qtextedit.h"
#include "QtNetwork/qhostinfo.h"
#include "QtNetwork/qhostaddress.h"
#include "QtNetwork/qnetworkinterface.h"
#include "QtNetwork"
#include "qtextstream.h"
#include "qmessagebox.h"

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

          tx->append(QString("%1").arg(line));

       }

    }

    inputFile.close();

    //Saving
    QFile w1(login);
    if(w1.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&w1);
        stream << tx->toPlainText();
        w1.flush();
        w1.close();
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
                continue;
            }

            tx->append(QString("%1").arg(line));
        }

    }

    inputFile2.close();

    //Saving
    QFile w2(chars);
    if(w2.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&w2);
        stream << tx->toPlainText();
        w2.flush();
        w2.close();
    }



    //Map

    tx->clear();
    QString map = root_path;
    map.append("/conf/map_athena.conf");
    QFile input3(map);
    if(input3.open(QIODevice::ReadOnly))
    {
        QTextStream in(&input3);
        while(!in.atEnd())
        {
            QString line = in.readLine();

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
            if(line.contains(tr("map_ip:")))
            {
                tx->append(QString("map_ip: %1").arg(ui->ipv6->text()));
                continue;
            }
            if(line.contains(tr("map_port:")))
            {
                tx->append(QString("map_port: %1").arg(ui->spinBox_3->value()));
                continue;
            }

            tx->append(QString("%1").arg(line));
        }
    }
    input3.close();



    //Saving
    QFile w3(map);
    if(w3.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&w3);
        stream << tx->toPlainText();
        w3.flush();
        w3.close();
    }




    //SQL Setting
    if(ui->radioButton_2->isChecked() == true)
    {
        tx->clear();
        QString inter = root_path;
        inter.append("/conf/inter_athena.conf");

        QFile input4(inter);
        if(input4.open(QIODevice::ReadOnly))
        {
            QTextStream in(&input4);
            while(!in.atEnd())
            {
             QString line = in.readLine();

             if(line.contains(tr("login_server_ip:")))
             {
                 tx->append(QString("login_server_ip: %1").arg(ui->dbhost->text()));
                 continue;
             }
             if(line.contains(tr("login_server_port:")))
             {
                 tx->append(QString("login_server_port: %1").arg(ui->dbport->text()));
                 continue;
             }
             if(line.contains(tr("login_server_id:")))
             {
                 tx->append(QString("login_server_id: %1").arg(ui->dbuser->text()));
                 continue;
             }
             if(line.contains(tr("login_server_pw:")))
             {
                 tx->append(QString("login_server_pw: %1").arg(ui->dbpass->text()));
                 continue;
             }
             if(line.contains(tr("login_server_db:")))
             {
                 tx->append(QString("login_server_db: %1").arg(ui->database->text()));
                 continue;
             }



             if(line.contains(tr("ipban_db_ip:")))
             {
                 tx->append(QString("ipban_db_ip: %1").arg(ui->dbhost->text()));
                 continue;
             }
             if(line.contains(tr("ipban_db_port:")))
             {
                 tx->append(QString("ipban_db_port: %1").arg(ui->dbport->text()));
                 continue;
             }
             if(line.contains(tr("ipban_db_id:")))
             {
                 tx->append(QString("ipban_db_id: %1").arg(ui->dbuser->text()));
                 continue;
             }
             if(line.contains(tr("ipban_db_pw:")))
             {
                 tx->append(QString("ipban_db_pw: %1").arg(ui->dbpass->text()));
                 continue;
             }
             if(line.contains(tr("ipban_db_db:")))
             {
                 tx->append(QString("ipban_db_db: %1").arg(ui->database->text()));
                 continue;
             }


             if(line.contains(tr("char_server_ip:")))
             {
                 tx->append(QString("char_server_ip: %1").arg(ui->dbhost->text()));
                 continue;
             }
             if(line.contains(tr("char_server_port:")))
             {
                 tx->append(QString("char_server_port: %1").arg(ui->dbport->text()));
                 continue;
             }
             if(line.contains(tr("char_server_id:")))
             {
                 tx->append(QString("char_server_id: %1").arg(ui->dbuser->text()));
                 continue;
             }
             if(line.contains(tr("char_server_pw:")))
             {
                 tx->append(QString("char_server_pw: %1").arg(ui->dbpass->text()));
                 continue;
             }
             if(line.contains(tr("char_server_db:")))
             {
                 tx->append(QString("char_server_db: %1").arg(ui->database->text()));
                 continue;
             }


             if(line.contains(tr("map_server_ip:")))
             {
                 tx->append(QString("map_server_ip: %1").arg(ui->dbhost->text()));
                 continue;
             }
             if(line.contains(tr("map_server_port:")))
             {
                 tx->append(QString("map_server_port: %1").arg(ui->dbport->text()));
                 continue;
             }
             if(line.contains(tr("map_server_id:")))
             {
                 tx->append(QString("map_server_id: %1").arg(ui->dbuser->text()));
                 continue;
             }
             if(line.contains(tr("map_server_pw:")))
             {
                 tx->append(QString("map_server_pw: %1").arg(ui->dbpass->text()));
                 continue;
             }
             if(line.contains(tr("map_server_db:")))
             {
                 tx->append(QString("map_server_db: %1").arg(ui->database->text()));
                 continue;
             }


             if(line.contains(tr("use_sql_db:")))
             {
                 tx->append(QString("use_sql_db: %1").arg("yes"));
                 continue;
             }

                 tx->append(QString("%1").arg(line));

            }

        }

        input4.close();


        //Saving
        QFile w4(inter);
        if(w4.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream stream(&w4);
            stream << tx->toPlainText();
            w4.flush();
            w4.close();
        }

    }


    //Subnet
    QString subnet = root_path;
    subnet.append("/conf/subnet_athena.conf");
    tx->clear();
    QFile input5(subnet);
    if(input5.open(QIODevice::ReadOnly))
    {
        QTextStream in(&input5);
        while(!in.atEnd())
        {

         QString line = in.readLine();


         if(line.contains(tr("subnet:")) && !line.startsWith(tr("//")) && !line.startsWith(tr(" ")))
         {
             tx->append(QString("%1:%2:%3").arg(ui->subnet->text(),ui->ipv6->text(),ui->ipv6->text()));
         }


        }



    }

    input5.close();

    //Saving
    QFile w5(subnet);
    if(w5.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&w5);
        stream << tx->toPlainText();
        w5.flush();
        w5.close();
    }




    QMessageBox::information(this,tr("Writing files..."),tr("Operation completed. You server are Ready to use."), QMessageBox::Ok);

}





