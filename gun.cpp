#include "gun.h"
#include <QImage>
#include <QBrush>
#include "item.h"

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

int Gun::Use()
{
    return 5;
}
