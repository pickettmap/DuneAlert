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
    Enemy(QPixmap &pixmap, int h, int d, Bounds b, std::vector<AttackPattern> a, std::string name, int gold, Item *item)
        : player(pixmap, h, d, b, gold) {
        a_ = a;
        name_ = name;
        item_  = item;
    }
    int getFightDuration();
    Item * getItem() { return item_; }
    std::string getName() { return name_; }

    std::vector<AttackPattern> GetFightPattern();


private:
    std::vector<AttackPattern> a_;
    std::string name_;
    Item * item_;

};

#endif // ENEMY_H
