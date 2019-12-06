#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "bullet.h"
#include <vector>

struct AttackPattern {
    int delay;
    int x;
    int y;
    Direction dir;
};

class Enemy : public player
{
public:
    Enemy(QPixmap &pixmap, int h, int d, Bounds b, std::vector<AttackPattern> a)
        : player(pixmap, h, d, b) {
        a_ = a;
    }
    std::vector<AttackPattern> GetFightPattern();

private:
    std::vector<AttackPattern> a_;
};

#endif // ENEMY_H
