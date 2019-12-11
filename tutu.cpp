#include "tutu.h"
#include "player.h"

/*
Function: Tutu constructor
Params: None
Desc: Initializes tutu picture, name, description, and item type
Returns: tutu
*/
Tutu::Tutu()
{
    QPixmap pm(":/images/Old_Tutu.png");
    pm = pm.scaled(50,50);
    setPixmap(pm);

    pm_ = pm;
    description_ = "+3 Max HP";
    name_ = "Old Tutu";
    itemtype_ = itemtype::Equipable;
}

/*
Function: Tutu use
Params: Player *p
Desc: Sets player maxhealth to 5
Returns: 0
*/
int Tutu::Use(player * p)
{
    p->setMaxHealth(3);
    return 0;
}
