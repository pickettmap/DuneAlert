#include "gun.h"
#include <QImage>
#include <QBrush>
#include "item.h"

Gun::Gun()
    : Item("Gun", "It's a gun idk")
{
    QPixmap pm(":/images/gun.png");
    pm = pm.scaled(50,50);
    setPixmap(pm);
}
