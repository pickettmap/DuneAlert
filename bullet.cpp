#include "bullet.h"

#include <QTimer>
#include <QBrush>

Bullet::Bullet()
{
    QPixmap qp(":/images/bullet.png");
    qp = qp.scaled(50, 50);
    setPixmap(qp);
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(travel()));
    timer->start(30);
}


void Bullet::travel() {
    //Proof of concept
    setX(x() + 20);
}
