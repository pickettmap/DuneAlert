#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "bullet.h"

struct AttackPattern {
    int delay;
    int x;
    int y;
    Direction dir;
};

class Enemy : public player
{
public:
    Enemy(QPixmap &pixmap, int h, int d, Bounds b)
        : player(pixmap, h, d, b) {

    }
    void TakeTurn();

private:
    int health_;
    int damage_;
};

#endif // ENEMY_H
