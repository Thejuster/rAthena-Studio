#ifndef SERVERSTART_H
#define SERVERSTART_H

#include <QDialog>

namespace Ui {
class ServerStart;
}

class ServerStart : public QDialog
{
    Q_OBJECT

public:
    explicit ServerStart(QWidget *parent = 0);
    ~ServerStart();
    QString root_path;

private slots:
    void on_pushButton_clicked();
    void processOutputLogin();
    void processOutputChars();
    void processOutputMap();

private:
    Ui::ServerStart *ui;
};

#endif // SERVERSTART_H
