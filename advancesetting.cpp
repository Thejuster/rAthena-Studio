#include "advancesetting.h"
#include "ui_advancesetting.h"
#include "qmessagebox.h"

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
