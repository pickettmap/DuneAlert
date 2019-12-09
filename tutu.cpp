#include "tutu.h"

Tutu::Tutu()
{
    QPixmap pm(":/images/Old_Tutu.png");
    pm = pm.scaled(50,50);
    setPixmap(pm);

    pm_ = pm;
    description_ = "An old tutu. Kind of ratty, but charming.";
    name_ = "Old Tutu";
    itemtype_ = itemtype::Equipable;
}

int Tutu::Use()
{
    return -2;
}
