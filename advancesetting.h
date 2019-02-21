#ifndef ADVANCESETTING_H
#define ADVANCESETTING_H

#include <QDialog>

namespace Ui {
class AdvanceSetting;
}

class AdvanceSetting : public QDialog
{
    Q_OBJECT
    
public:
    explicit AdvanceSetting(QWidget *parent = 0);
    ~AdvanceSetting();
    void pre_load();
    bool console_command = false;
    bool account_m_f = false;
    bool md5 = false;
    QString root_path;
    void Shown();
    void LoadSetting();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AdvanceSetting *ui;


};

#endif // ADVANCESETTING_H
