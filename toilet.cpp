#include "toilet.h"
#include <QImage>
#include <QBrush>
#include "item.h"

/*
Function: Toilet constructor
Params: None
Desc: Initializes toilet picture, name, description, and item type
Returns: Toilet
*/
Toilet::Toilet()
{
    QPixmap pm(":/images/toiletchan.png");
    pm = pm.scaled(50,50, Qt::KeepAspectRatioByExpanding);
    setPixmap(pm);

    pm_ = pm;
    description_ = "The throne. You feel like a king.";
    name_ = "Toilet";
    itemtype_ = itemtype::Scenery;
    flushed_=false;
}

/*
Function: Use
Params: None
Desc: Does nothing, never called
Returns: NULL
*/
int Toilet::Use()
{
    return NULL;
}
