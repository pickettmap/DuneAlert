#include "bullet.h"

#include <QTimer>
#include <QBrush>
#include "player.h"
#include "enemy.h"
#include <QGraphicsScene>
#include <QMediaPlayer>

/*
Function: Bullet Constructor
Params: int x, int y, Direction, scene, bound
Desc: Instantiates bullet class given certain perams
Returns: none
*/
Bullet::Bullet(int x, int y, Direction dir, QGraphicsScene * scene, Bounds bound)
{
    this->scene = scene;
    dir_ = dir;
    QPixmap qp(":/images/bullet.png");
    qp = qp.scaled(30, 30);
    setPixmap(qp);
    //Start the timer for bullet movement
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Travel()));
    timer->start(30);
    setPos(x, y);
    bound_ = bound;
}

/*
Function: travel
Params: none
Desc: Travels in a given direction every tick
Returns: none
*/

void Bullet::Travel() {
    if (x() < bound_.x1 || x() > bound_.x2 || y() < bound_.y1 || y() > bound_.y2) {
        scene->removeItem(this);
        delete this;
        return;
    }
    if (delay_timer > 0) {
        delay_timer --;
        return;
    }
    //Move in the correct direction given
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
    //If the bullet collides with a player, the player should lose health!
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (size_t i = 0,n = colliding_items.size(); i < n; ++i){
        if (dynamic_cast<Player *>(colliding_items[i]) && !dynamic_cast<Enemy *>(colliding_items[i])){
            this->scene->removeItem(this);
            Player * p = static_cast<Player *>(colliding_items[i]);
            p->changeHealth(-1);
            this->scene->update();
            QMediaPlayer * sound = new QMediaPlayer();
            sound->setMedia(QUrl(":/sounds/hit.wav"));
            sound->play();
            delete this;
            return;
        }
    }
}
