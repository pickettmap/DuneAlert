#ifndef TUTU_H
#define TUTU_H

#include "item.h"

class Tutu : public Item
{
public:
    Tutu();
    int Use(player * p);
};

#endif // TUTU_H
