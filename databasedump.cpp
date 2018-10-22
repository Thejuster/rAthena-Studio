#include "databasedump.h"
#include "ui_databasedump.h"

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
