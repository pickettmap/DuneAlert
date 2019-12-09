#include "toilet.h"
#include <QImage>
#include <QBrush>
#include "item.h"

Toilet::Toilet()
{
    QPixmap pm(":/images/toiletchan.png");
    pm = pm.scaled(50,50, Qt::KeepAspectRatioByExpanding);
    setPixmap(pm);

    pm_ = pm;
    description_ = "The throne. You feel like a king.";
    name_ = "Toilet";
    itemtype_ = itemtype::Scenery;
}

int Toilet::Use()
{
    return NULL;
}
