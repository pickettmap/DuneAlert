#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>

class Item : public QGraphicsPixmapItem
{
public:
    Item(std::string name, std::string description);
    virtual void use();
    int getID(){return item_id_;}
    std::string getName() {return name_;}
    std::string getDescription() {return description_;}
private:
    int item_id_;
    std::string name_;
    std::string description_;
};

#endif // ITEM_H
