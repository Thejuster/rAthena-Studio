#include "advancesetting.h"
#include "ui_advancesetting.h"
#include "qmessagebox.h"
#include "qdatastream.h"
#include "qtextstream.h"
#include "qmessagebox.h"
#include "qregexp.h"

AdvanceSetting::AdvanceSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvanceSetting)
{

    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
}

AdvanceSetting::~AdvanceSetting()
{
    delete ui;
}


void AdvanceSetting::on_pushButton_clicked()
{
    QMessageBox::information(this,tr("HINT"),tr(
                                 "Format: <id>,<amount>,<position>: ..."), QMessageBox::Ok);
}

void AdvanceSetting::on_pushButton_2_clicked()
{
    QMessageBox::information(this,tr("Hint"),tr("Don't add spaces unless you mean to add 'space' to the list."),QMessageBox::Ok);
}

void AdvanceSetting::Shown()
{
    if(root_path.length() > 0)
        {
            pre_load();
        }else
        {
            QMessageBox::warning(this,tr("Warning!"),tr("Plase select first rAthena Main folder"),QMessageBox::Ok);
            this->reject();

            ui->groupBox->setEnabled(false);
            ui->groupBox_2->setEnabled(false);
            ui->groupBox_3->setEnabled(false);
            ui->groupBox_4->setEnabled(false);
            ui->groupBox_5->setEnabled(false);
            ui->groupBox_6->setEnabled(false);
            ui->groupBox_7->setEnabled(false);
            ui->buttonBox->setEnabled(false);
        }

}

void AdvanceSetting::on_buttonBox_accepted()
{

    if(ui->checkBox_2->isChecked())
        console_command=true;

    if(ui->checkBox_3->isChecked())
        account_m_f = true;

    if(ui->checkBox_4->isChecked())
        md5 = true;


    this->accept();
}

void AdvanceSetting::on_buttonBox_rejected()
{
    this->reject();
}



void AdvanceSetting::pre_load()
{

    QTextEdit *tx = new QTextEdit;

    //Loading Settings
    QString login = root_path;
    login.append("/conf/login_athena.conf");

    QFile inputFile(login);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();

          //Find consoel command
          if(line.contains(tr("console:")) && !line.contains(tr("_")))
          {

              //Console command
              QRegExp rx("(\\ |\\,|\\.|\\:|\\t)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
              QStringList query = line.split(rx);
              if(query[2].contains("on"))
                  ui->checkBox_2->setChecked(true);
              else
                  ui->checkBox_2->setChecked(false);



              continue;
          }

       }

    }

}


