#ifndef NPCEDITOR_H
#define NPCEDITOR_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>
#include <QPoint>
#include <QPaintEvent>

namespace Ui {
class NPCEditor;
}

class NPCEditor : public QWidget
{
    Q_OBJECT

public:
    explicit NPCEditor(QWidget *parent = nullptr);
    ~NPCEditor();
     QGraphicsItem *item;
     QGraphicsItem *item2;
     QGraphicsItem *line;
     QGraphicsScene *scene;

private slots:
     void on_pushButton_clicked();

public:
     void Connect(QGraphicsItem *src, QGraphicsItem *dest);


     struct connection
     {
        public:
         QGraphicsItem *src;
         QGraphicsItem *dest;
         QGraphicsLineItem *connected;
     };

     QList<connection> Connections;

protected:
   void paintEvent(QPaintEvent * event);


private:
    Ui::NPCEditor *ui;
};

#endif // NPCEDITOR_H
