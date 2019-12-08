#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>

class Item : public QGraphicsPixmapItem
{
public:
    Item();
    virtual void use();
    int getID(){return item_id_;}

private:
    int item_id_;
};

#endif // ITEM_H
