#include "burger.h"
#include <QImage>
#include <QBrush>
#include "item.h"
#include "player.h"

/*
Function: Burger constructor
Params: None
Desc: Initializes burger picture, name, description, and item type
Returns: Burger
*/
Burger::Burger()
{
    QPixmap pm(":/images/Glamburger.png");
    pm = pm.scaled(50,50);
    setPixmap(pm);

    pm_ = pm;
    description_ = "+5 HP";
    name_ = "Glamburger";
    itemtype_ = itemtype::Consumable;
}

/*
Function: Use
Params: Player *p
Desc: Changes player's health by 5
Returns: 0
*/
int Burger::Use(player * p)
{
    p->changeHealth(5);
    return 0;
}
