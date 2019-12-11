#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>
#include <QGraphicsItem>
#include <player.h>

enum Direction { N, NE, E, SE, S, SW, W, NW};

class Bullet: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(int x, int y, Direction dir, QGraphicsScene * scene, Bounds bound);
public slots:
    void Travel();

private:
    Direction dir_;
    int delay_timer = 20;
    QGraphicsScene * scene;
    Bounds bound_;
};

#endif // BULLET_H
