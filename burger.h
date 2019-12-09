#ifndef BURGER_H
#define BURGER_H

#include "item.h"

class Burger : public Item
{
public:
    Burger();
    int Use();
};

#endif // BURGER_H
