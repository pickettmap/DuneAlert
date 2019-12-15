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

Item * ItemFactory::GetRandomItem() {
    Rock * r = new Rock();
    Tutu * t = new Tutu();
    PiggyBank * b = new PiggyBank();
    Sword * s = new Sword();
    Gun * g = new Gun();
    Fruit * f = new Fruit();
    Item * arr[6] = {r, t, b, s, f, g};
    int rand_item = rand() % 6;
    qDebug() << rand_item;
    return arr[rand_item];
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

int PiggyBank::Use(Player * p) {
    p->changeGold(5);
    return 0;
}

int FinalPaper::Use(Player * p) {
    p->changeGold(10);
    p->changeHealth(-10);
    return 0;
}

int Rock::Use(Player * p) {
    return 0;
}

int Tutu::Use(Player * p)
{
    p->setMaxHealth(1);
    return 0;
}

int Gun::Use(Player * p) {
    p->setDamage(1);
    return 0;
}

int Sword::Use(Player * p) {
    p->setDamage(-1);
    p->changeGold(10);
    return 0;
}

int Tuna::Use(Player * p) {
    p->setMaxHealth(3);
    return 0;
}

int Whoopass::Use(Player * p) {
    p->setDamage(1);
    p->changeGold(-10);
    return 0;
}

int Fruit::Use(Player * p) {
    p->setDamage(1);
    p->changeHealth(-15);
    return 0;
}

int Dog::Use(Player * p) {
    p->setDamage(3);
    p->changeGold(-30);
    return 0;
}

