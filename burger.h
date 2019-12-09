#ifndef BURGER_H
#define BURGER_H

#include "item.h"

class Burger : public Item
{
public:
    Burger();
    int Use(player * p);
};

#endif // BURGER_H
