#include "gameview.h"
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <QDebug>

GameView::GameView()
{
    scene = new QGraphicsScene(this);

    scene->setSceneRect(0, 0, width(), height());

    QGraphicsRectItem *rec = new QGraphicsRectItem(QRect(0,0,200,200));
    scene->addItem(rec);

    setScene(scene);
    setSceneRect(scene->sceneRect());

    setMinimumSize(1000,800);
    setWindowTitle("Village Defense");
}
