#include "enemy.h"

std::vector<AttackPattern> Enemy::GetFightPattern() {
    return a_;
}

int Enemy::getFightDuration() {
    return a_.back().delay + 1000;
}
