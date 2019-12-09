#ifndef INVENTORY_H
#define INVENTORY_H

#include <QObject>
#include <QGraphicsRectItem>
#include "item.h"
#include <QGraphicsTextItem>

class Inventory : public QObject, public QGraphicsItem
{
public:
    Inventory();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void AddItem(Item *item);

    Item* GetItem(int index);
    void RemoveItem(int index);
    int GetConsumableItemsCount() { return int(consumable_items_.size());}

    void UseItem();

    void setPos(int x, int y);

private:
    int width_ = 150;
    int x_ = 20;
    int y_ = 20;
    std::vector<Item*> consumable_items_;
    std::vector<Item*> equipable_items_;

};

#endif // INVENTORY_H
