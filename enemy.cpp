#include "enemy.h"
/*
Function: GetFightPattern
Params: none
Desc: returns an enemies fight pattern
Returns: vector of attack patterns
*/
std::vector<AttackPattern> Enemy::GetFightPattern() {
    return a_;
}

/*
Function: GetFightDuration
Params: none
Desc: Returns the total length of the fight to guard against unsafe inputs
Returns: int duration of fight
*/
int Enemy::getFightDuration() {
    return a_.back().delay + 1000;
}
