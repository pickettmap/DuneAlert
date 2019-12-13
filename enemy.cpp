#include "enemy.h"
#include <QDebug>
/*
Function: GetFightPattern
Params: none
Desc: returns an enemies fight pattern
Returns: vector of attack patterns
*/
std::vector<AttackPattern> Enemy::GetFightPattern() {
    int number_of_patterns = int(a_.size());
    int selection = rand() % number_of_patterns;
    return a_[selection];
}

/*
Function: GetFightDuration
Params: none
Desc: Returns the total length of the fight to guard against unsafe inputs
Returns: int duration of fight
*/
int Enemy::getFightDuration() {
    return 0;
}
