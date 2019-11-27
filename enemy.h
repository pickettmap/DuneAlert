#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"


class Enemy : public player
{
public:
    void TakeTurn();
};

#endif // ENEMY_H
