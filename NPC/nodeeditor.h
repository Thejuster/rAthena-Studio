#ifndef NODEEDITOR_H
#define NODEEDITOR_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

class NodeEditor : public QGraphicsView
{

    Q_OBJECT
public:
    explicit NodeEditor(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // NODEEDITOR_H
