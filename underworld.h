#ifndef UNDERWORLD_H
#define UNDERWORLD_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "bullet.h"
#include "enemy.h"


class Underworld : public QGraphicsView
{
   Q_OBJECT
public:
    Underworld(QGraphicsScene * scene);
    void ProcessAttackPattern(std::vector<AttackPattern> a);
public slots:
    void FireBullet(int x, int y);

public:
signals:
    void OnBulletFired(int x, int y);

private:
    QGraphicsScene * scene;
};

#endif // UNDERWORLD_H
