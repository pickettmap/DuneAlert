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


#endif // ITEM_H
