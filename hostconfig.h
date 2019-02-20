#ifndef HOSTCONFIG_H
#define HOSTCONFIG_H

#include <QDialog>

namespace Ui {
class HostConfig;
}

class HostConfig : public QDialog
{
    Q_OBJECT
    
public:
    explicit HostConfig(QWidget *parent = 0);
    QString root_path;
    ~HostConfig();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_pressed();

private:
    Ui::HostConfig *ui;
};

#endif // HOSTCONFIG_H
