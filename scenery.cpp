#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsTextItem>

#include "scenery.h"

Scenery::Scenery()
{
    itemtype_ = itemtype::Scenery;
    touched_ = false;
}

Toilet::Toilet() : Scenery()
{
    QPixmap pm(":/images/toiletchan.png");
    pm = pm.scaled(50,50, Qt::KeepAspectRatioByExpanding);
    setPixmap(pm);

    pm_ = pm;
    description_ = "The throne. You feel like a king.";
    name_ = "Toilet";
}

void Toilet::Touched() {
    setTouched(true);
    QPixmap pm(":/images/darktoiletchan.png");
    pm = pm.scaled(50,50, Qt::KeepAspectRatioByExpanding);
    setPixmap(pm);
    pm_ = pm;
}

Chest::Chest() : Scenery()
{
    QPixmap pm(":/images/chest_open.png");
    pm = pm.scaled(50,50, Qt::KeepAspectRatioByExpanding);
    setPixmap(pm);

    pm_ = pm;
    description_ = "Treasure, don't mind if I do.";
    name_ = "Treasure";
    itemtype_ = itemtype::Scenery;
}

void Chest::Touched() {
    setTouched(true);
    QPixmap pm(":/images/chest_close.png");
    pm = pm.scaled(50,50, Qt::KeepAspectRatioByExpanding);
    setPixmap(pm);
    pm_ = pm;
}

Crate::Crate() : Scenery()
{
    QPixmap pm(":/images/box.png");
    pm = pm.scaled(50,50, Qt::KeepAspectRatioByExpanding);
    setPixmap(pm);

    pm_ = pm;
    description_ = "Treasure, don't mind if I do.";
    name_ = "Treasure";
    itemtype_ = itemtype::Scenery;

}

void Crate::Touched() {
    setTouched(true);
    QPixmap pm(":/images/used_box.png");
    pm = pm.scaled(50,50, Qt::KeepAspectRatioByExpanding);
    setPixmap(pm);
    pm_ = pm;
}
