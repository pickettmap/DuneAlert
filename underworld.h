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
    void InitiateFightSequence();
    void OnItemUsed();

//    void DrawInventory();
public slots:
    void FireBullet(int x, int y, Direction d);
    void OnFightClicked();
    void SwitchToOverWorld();
    void OnKeyPress(QKeyEvent *event);
    void OnPlayerDeath();

public:
signals:
    void OnBulletFired(int x, int y, Direction d);
    void OnEnemyHit(int amount);

private:
    ContainingBox * fight_box_;
    ContainingBox * bribe_box_;
    QGraphicsScene * scene_;
    Enemy * enemy_;
    player * player_;
    bool fighting_ = false;
    bool fight_over_ = false;
    int cx1_;
    int cy1_;
    int cx2_;
    int cy2_;
};

#endif // UNDERWORLD_H
