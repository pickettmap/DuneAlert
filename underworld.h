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
    void MakeAIChoice();

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
    QTimer * ai_timer;
};

#endif // UNDERWORLD_H
