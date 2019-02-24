#include "serverstart.h"
#include "ui_serverstart.h"
#include "qthread.h"
#include "qdebug.h"
#include "qprocess.h"

ServerStart::ServerStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerStart)
{
    ui->setupUi(this);
}

ServerStart::~ServerStart()
{
    delete ui;
}

QProcess *proc;
QProcess *proc2;
QProcess *proc3;

void ServerStart::on_pushButton_clicked()
{
    QString login = QString("%1/%2").arg(root_path).arg("login-server.exe");
    QString chars = QString("%1/%2").arg(root_path).arg("char-server.exe");
    QString map = QString("%1/%2").arg(root_path).arg("map-server.exe");

    proc = new QProcess(this);
    proc2 = new QProcess(this);
    proc3 = new QProcess(this);

    connect(proc,SIGNAL(readyReadStandardOutput()),this,SLOT(processOutputLogin()));
    connect(proc2,SIGNAL(readyReadStandardOutput()),this,SLOT(processOutputChars()));
    connect(proc3,SIGNAL(readyReadStandardOutput()),this,SLOT(processOutputMap()));

    proc->start(login);
    proc2->start(chars);
    proc3->start(map);
}

void ServerStart::processOutputLogin()
{

  ui->plainTextEdit->appendPlainText(proc->readAllStandardOutput());
}


void ServerStart::processOutputChars()
{
    ui->plainTextEdit_2->appendPlainText(proc2->readAllStandardOutput());
}

void ServerStart::processOutputMap()
{
    ui->plainTextEdit_3->appendPlainText(proc3->readAllStandardOutput());
}
