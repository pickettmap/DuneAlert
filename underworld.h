#ifndef UNDERWORLD_H
#define UNDERWORLD_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "bullet.h"


class Underworld : public QGraphicsView
{
public:
    Underworld(QGraphicsScene * scene);
    void ExampleAttackPattern();
public slots:
    void FireBullet();

private:
    QGraphicsScene * scene;
};

#endif // UNDERWORLD_H
