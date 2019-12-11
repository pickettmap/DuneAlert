#include "item.h"
#include "gameview.h"
#include "player.h"

Item::Item(){}
/*
Function: Item Constructor
Params: name, description type
Desc: Instantiates Item class
Returns: none
*/
Item::Item(std::string name, std::string description, itemtype type)
{
    name_ = name;
    description_ = description;
    itemtype_ = type;
}

/*
Function: Use
Params: player p
Desc: Given a player, use an item and change players stats accordingly.
Returns: none
*/
int Item::Use(Player * p)
{
    //handled in derived classes
    return -1;
}
