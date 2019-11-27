#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>
#include <QGraphicsItem>

enum Direction { N, NE, E, SE, S, SW, W, NW};

class Bullet: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(int x, int y, Direction dir);
public slots:
    void travel();

private:
    Direction dir_;
    int delay_timer = 20;
};

#endif // BULLET_H
