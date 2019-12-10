#ifndef TOILET_H
#define TOILET_H

#include "item.h"

class Toilet : public Item
{
public:
    Toilet();
    int Use();
    void Flush(){flushed_=true;}
    bool getFlush(){return flushed_;}
private:
    bool flushed_;
};

#endif // TOILET_H
