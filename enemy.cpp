#include "enemy.h"

std::vector<AttackPattern> Enemy::GetFightPattern(int turn) {
    int current_delay = 0;
//  Bounds bound = {100, 100, 600, 400};
    std::vector<AttackPattern> a;
    for (int i = 0; i < 50; i ++) {
        current_delay += 100;
        AttackPattern p = {current_delay, 100 + i * 5, 110, Direction::S};
        a.push_back(p);
    }
        current_delay += 1000;
    for (int i = 0; i < 50; i ++) {
        current_delay += 100;
        AttackPattern p = {current_delay, 100 + i * 5, 390, Direction::N};
        a.push_back(p);
    }
        current_delay += 1000;
    for (int i = 0; i < 50; i ++) {
        current_delay += 100;
        AttackPattern p = {current_delay, 100 + i * 5, 390, Direction::NE};
        a.push_back(p);
    }

    return a;
}
