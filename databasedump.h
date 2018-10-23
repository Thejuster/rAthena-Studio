#ifndef DATABASEDUMP_H
#define DATABASEDUMP_H

#include <QDialog>

namespace Ui {
class DatabaseDump;
}

class DatabaseDump : public QDialog
{
    Q_OBJECT
    
public:
    explicit DatabaseDump(QWidget *parent = 0);
    ~DatabaseDump();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::DatabaseDump *ui;
};

#endif // DATABASEDUMP_H
