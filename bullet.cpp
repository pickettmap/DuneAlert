#include "bullet.h"

#include <QTimer>
#include <QBrush>

Bullet::Bullet(int x, int y, Direction dir)
{
    dir_ = dir;
    QPixmap qp(":/images/bullet.png");
    qp = qp.scaled(50, 50);
    setPixmap(qp);
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(travel()));
    timer->start(30);
    setPos(x, y);
}


void Bullet::travel() {
    if (delay_timer > 0) {
        delay_timer --;
        return;
    }
    if (dir_ == Direction::S) {
        setY(y() + 10);
    }
}
