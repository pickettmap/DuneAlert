#include "bullet.h"

#include <QTimer>
#include <QBrush>

Bullet::Bullet()
{
    setPixmap(QPixmap(":/images/bullet_temp.jpg"));
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(travel()));
    timer->start(30);
}


void Bullet::travel() {
    //Proof of concept
    setX(x() + 0.5);
}
