#include "item.h"
#include "gameview.h"
#include "player.h"

Item::Item(){}

Item::Item(std::string name, std::string description, itemtype type)
{
    name_ = name;
    description_ = description;
    itemtype_ = type;
}

int Item::Use()
{
    //handled in derived classes
    return -1;
}
