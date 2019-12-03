#include "bullet.h"

#include <QTimer>
#include <QBrush>
#include "player.h"
#include <QGraphicsScene>

Bullet::Bullet(int x, int y, Direction dir, QGraphicsScene * scene, Bounds bound)
{
    this->scene = scene;
    dir_ = dir;
    QPixmap qp(":/images/bullet.png");
    qp = qp.scaled(50, 50);
    setPixmap(qp);
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(travel()));
    timer->start(30);
    setPos(x, y);
    bound_ = bound;
}


void Bullet::travel() {
    if (x() < bound_.x1 || x() > bound_.x2 || y() < bound_.y1 || y() > bound_.y2) {
        scene->removeItem(this);
        delete this;
        return;
    }
    if (delay_timer > 0) {
        delay_timer --;
        return;
    }

    switch (dir_) {
        case(Direction::S):
            setY(y() + 10);
            break;
        case(Direction::N):
            setY(y() - 10);
            break;
        case(Direction::W):
            setX(x() - 10);
            break;
        case(Direction::E):
            setX(x() + 10);
            break;
        case(Direction::NE):
            setY(y() - 10);
            setX(x() + 10);
            break;
        case(Direction::NW):
            setY(y() - 10);
            setX(x() - 10);
            break;
        case(Direction::SE):
            setY(y() + 10);
            setX(x() + 10);

            break;
        case(Direction::SW):
            setY(y() + 10);
            setX(x() - 10);
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (size_t i = 0,n = colliding_items.size(); i < n; ++i){
        // if the arrow collides with a wall, delete it
        if (dynamic_cast<player *>(colliding_items[i])){
            this->scene->removeItem(this);
            player * p = static_cast<player *>(colliding_items[i]);
            p->changeHealth(-1);
            delete this;
            return;
        }
    }
}
