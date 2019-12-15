#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>

enum class itemtype {Equipable, Consumable, Scenery};

class Player;

class Item : public QGraphicsPixmapItem
{
public:
    Item();
    Item(std::string name, std::string description, itemtype type);

    //returns amount to change stat by (health, atk, or def)
    virtual int Use(Player * p);

    void SetDescription(std::string desc) {description_= desc;}

    //int getID(){return item_id_;}
    std::string getName() {return name_;}
    std::string getDescription() {return description_;}
    itemtype getItemType() {return itemtype_;}
    QPixmap getPixmap(){return pm_;}

protected:
    itemtype itemtype_;
    QPixmap pm_;

    //maybe not needed
    //int item_id_;
    std::string name_;
    std::string description_;
};

class PiggyBank : public Item
{
public:
    PiggyBank::PiggyBank()
        : Item("Piggy Bank", "+5 Gold", itemtype::Consumable) {}
    int Use(Player * p);
};


class FinalPaper : public Item
{
public:
    FinalPaper::FinalPaper()
        : Item("Final Paper", "+10 G -10 HP", itemtype::Consumable) {}

    int Use(Player * p);
};

class Rock : public Item
{
public:
    Rock::Rock()
        : Item("Rock", "Does Nothing", itemtype::Equipable) {}

    int Use(Player * p);
};

class Tutu : public Item
{
public:
    Tutu()
        : Item("Tutu", "+1 Max Health", itemtype::Equipable) {}

    int Use(Player * p);
};

class Burger : public Item
{
public:
    Burger()
        : Item("GlamBurger", "+5 Health", itemtype::Consumable) {}

    int Use(Player * p);
};

class Gun : public Item
{
public:
    Gun()
        : Item("A Gun", "+1 Damage", itemtype::Equipable) {}

    int Use(Player * p);
};

class Sword : public Item
{
public:
    Sword()
        : Item("Blood Knife", "-1 DPS +10 G", itemtype::Consumable) {}

    int Use(Player * p);
};

class Tuna : public Item
{
public:
    Tuna()
        : Item("Fish Hat", "+3 Max Health", itemtype::Equipable) {}

    int Use(Player * p);
};

class Whoopass : public Item
{
public:
    Whoopass()
        : Item("Can-o-Whoopass", "+1 DPS, -10 G", itemtype::Consumable) {}

    int Use(Player * p);
};

class Fruit : public Item
{
public:
    Fruit()
        : Item("Rotten Fruit", "-15 Health, +1 DPS", itemtype::Consumable) {}

    int Use(Player * p);
};

class Dog : public Item
{
public:
    Dog()
        : Item("A Small Dog", "+3 DPS, - 30 G", itemtype::Consumable) {}

    int Use(Player * p);
};


class ItemFactory {
public:
    static Item * GetRandomItem();
};


#endif // ITEM_H
