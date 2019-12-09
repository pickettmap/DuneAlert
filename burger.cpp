#include "burger.h"
#include <QImage>
#include <QBrush>
#include "item.h"
#include "player.h"

Burger::Burger()
{
    QPixmap pm(":/images/Glamburger.png");
    pm = pm.scaled(50,50);
    setPixmap(pm);

    pm_ = pm;
    description_ = "A Glamburger. You feel sparkly and poor.";
    name_ = "Glamburger";
    itemtype_ = itemtype::Consumable;
}

int Burger::Use(player * p)
{
    p->changeHealth(5);
    return 0;
}
