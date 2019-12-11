#ifndef GUN_H
#define GUN_H

#include "item.h"
#include "player.h"

class Gun : public Item{
public:
    Gun();
    int Use(Player *p);
};

#endif // GUN_H
