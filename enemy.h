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
    Enemy(QPixmap &pixmap, int h, int d, Bounds b)
        : player(pixmap, h, d, b) {
    }
    std::vector<AttackPattern> GetFightPattern(int turn);
};

#endif // ENEMY_H
