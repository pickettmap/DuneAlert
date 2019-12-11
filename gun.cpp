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
    description_ = "An old gun. A relic of the ancient CattleMen of old.";
    name_ = "Gun";
    itemtype_ = itemtype::Equipable;
}

/*
Function: Gun use
Params: Player *p
Desc: Sets player damage to 5
Returns: 0
*/
int Gun::Use(player *p)
{
    p->setDamage(5);
    return 0;
}
