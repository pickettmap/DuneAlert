#ifndef UNDERWORLD_H
#define UNDERWORLD_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "bullet.h"
#include "enemy.h"
#include "containingbox.h"

class Underworld : public QGraphicsView
{
   Q_OBJECT
public:
    Underworld(QGraphicsScene * scene, Enemy * e, player * p);
    void ProcessAttackPattern(std::vector<AttackPattern> a);
    void EndBattle();
public slots:
    void FireBullet(int x, int y, Direction d);
    void onFightClicked();
    void SwitchToOverWorld();

public:
signals:
    void OnBulletFired(int x, int y, Direction d);
    void OnEnemyHit(int amount);

private:
    QGraphicsScene * scene;
    Enemy * e;
    player * p;
    ContainingBox *continue_;
};

#endif // UNDERWORLD_H
