#include "gun.h"
#include <QImage>
#include <QBrush>
#include "item.h"

/*
Function: Gun constructor
Params: None
Desc: Initializes Gun picture, name, description, and item type
Returns: Gun
*/
Gun::Gun()
{
    QPixmap pm(":/images/gun.png");
    pm = pm.scaled(50,50);
    setPixmap(pm);

    pm_ = pm;
    description_ = "+1 Damage";
    name_ = "Gun";
    itemtype_ = itemtype::Equipable;
}

/*
Function: Gun use
Params: Player *p
Desc: Sets player damage to 5
Returns: 0
*/
int Gun::Use(Player *p)
{
    p->setDamage(1);
    return 0;
}
