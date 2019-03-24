#include "npceditor.h"
#include "ui_npceditor.h"
#include "qgraphicsitem.h"
#include "qdebug.h"
#include "QPaintEvent"

NPCEditor::NPCEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NPCEditor)
{

   ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    item = new QGraphicsTextItem(QString("TESTO A"));
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(item);

    item2 = new QGraphicsTextItem(QString("TESTO B"));
    item2->setFlag(QGraphicsItem::ItemIsMovable);
    item2->setFlag(QGraphicsItem::ItemIsFocusable);

    scene->addItem(item2);





}

NPCEditor::~NPCEditor()
{
    delete ui;
}


void NPCEditor::Connect(QGraphicsItem *src, QGraphicsItem *dest)
{
    NPCEditor::connection conn;
    conn.src = src;
    conn.dest = dest;

    conn.connected = new QGraphicsLineItem(src->x(),src->y(),dest->x(),dest->y());

    scene->addItem(conn.connected);
    Connections.append(conn);
}


void NPCEditor::paintEvent(QPaintEvent *e)
{


    for(int i = 0; i < scene->items().count(); i++)
    {

        QGraphicsLineItem *linea = dynamic_cast<QGraphicsLineItem*>(scene->items().at(i));
        if(linea)
        {
            scene->items().removeAt(i);
        }
         qDebug() << &linea;
    }


    /*for(int i = 0; i < Connections.count();i++)
    {
       NPCEditor::connection conn = Connections[i];
       QGraphicsLineItem *it = new QGraphicsLineItem(Connections[i].src->x(),Connections[i].src->y(),Connections[i].dest->x(),Connections[i].dest->y());
       conn.connected = it;
       Connections.replace(i,conn);

    scene->addItem(conn.connected);
    }*/


    update();
}


void NPCEditor::on_pushButton_clicked()
{

    Connect(item,item2);


    /*
    line = new QGraphicsLineItem(item->x(),item->y(),item2->x(),item2->y());
    line->setFlag(QGraphicsItem::ItemIsFocusable);

    scene->addItem(line);*/

}
