#include "tutu.h"
#include "player.h"

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

int Tutu::Use(player * p)
{
    p->setMaxHealth(3);
    return 0;
}
