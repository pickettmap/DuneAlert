#include "gun.h"
#include <QImage>
#include <QBrush>
#include "item.h"

Gun::Gun()
{
    QPixmap pm(":/images/gun.png");
    pm = pm.scaled(50,50);
    setPixmap(pm);
}
