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

class Enemy : public Player
{
public:
    Enemy(QPixmap &pixmap, int h, int d, Bounds b, std::vector<std::vector<AttackPattern>> a, std::string name, int gold, Item *item, std::string music)
        : Player(pixmap, h, d, b, gold) {
        a_ = a;
        name_ = name;
        item_  = item;
        music_ = QString::fromStdString(music);
    }
    int getFightDuration();
    Item * getItem() { return item_; }
    QString getMusic() { return music_; }
    std::string getName() { return name_; }

    std::vector<AttackPattern> GetFightPattern();


private:
    std::vector<std::vector<AttackPattern>> a_;
    std::string name_;
    Item * item_;
    QString music_;

};

#endif // ENEMY_H
