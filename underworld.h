#ifndef UNDERWORLD_H
#define UNDERWORLD_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "bullet.h"
#include "enemy.h"
#include "containingbox.h"

class Underworld: public QObject
{
   Q_OBJECT
public:
    Underworld(QGraphicsScene * scene);
    void DrawUnderworld(Enemy * e, player *p);
    void ProcessAttackPattern(std::vector<AttackPattern> a);
    void EndBattle(QString s);
    void Bribe();
    void EnemyDeath();

//    void DrawInventory();
public slots:
    void FireBullet(int x, int y, Direction d);
    void onFightClicked();
    void SwitchToOverWorld();
    void onKeyPress(QKeyEvent *event);
    void onPlayerDeath();

public:
signals:
    void OnBulletFired(int x, int y, Direction d);
    void OnEnemyHit(int amount);

private:
    ContainingBox * fight_box_;
    ContainingBox * bribe_box_;
    QGraphicsScene * scene_;
    Enemy * e_;
    player * p_;
    ContainingBox *continue_;
    bool fighting_ = false;
};

#endif // UNDERWORLD_H
