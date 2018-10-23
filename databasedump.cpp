#include "databasedump.h"
#include "ui_databasedump.h"
#include "qmessagebox.h"


DatabaseDump::DatabaseDump(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseDump)
{
    ui->setupUi(this);
}

DatabaseDump::~DatabaseDump()
{
    delete ui;
}

void DatabaseDump::on_pushButton_clicked()
{
    QMessageBox::information(this,tr("ciao"),tr("ciao2333"),QMessageBox::Ok);
}
