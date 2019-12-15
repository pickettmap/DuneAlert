#ifndef SCENERY_H
#define SCENERY_H
#include <item.h>


class Scenery: public Item
{
public:
    Scenery();
    virtual void Touched(){touched_=true;}
    bool getTouched(){return touched_;}
    void setTouched(bool touched) { touched_ = touched ; }

private:
    bool touched_;
};

class Toilet : public Scenery
{
public:
    Toilet();
    void Touched();


};

class Chest : public Scenery
{
public :
    Chest();
    void Touched();
};


class Crate : public Scenery
{
public:
    Crate();
    void Touched();
};

#endif // SCENERY_H
