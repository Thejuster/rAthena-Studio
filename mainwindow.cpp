#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfile.h"
#include "qtextstream.h"
#include "qmessagebox.h"
#include "qfiledialog.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap logo = QPixmap(":/new/images/logo.png");

    int w = std::min(logo.width(),  ui->label->maximumWidth());
    int h = std::min(logo.height(), ui->label->maximumHeight());

    logo = logo.scaled(QSize(w, h), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label->setPixmap(logo);


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    HostConfig *conf = new HostConfig();
    conf->exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    DatabaseDump *db = new DatabaseDump();
    db->exec();
}
