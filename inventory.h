#ifndef INVENTORY_H
#define INVENTORY_H

#include <QObject>
#include <QGraphicsRectItem>
#include "item.h"
#include <QGraphicsTextItem>

class Inventory : public QObject, public QGraphicsItem
{
public:
    Inventory(int x, int y);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void UpdateInventory();
    void AddItem(Item *item);

    void UseItem();

    std::vector<Item*> items;

private:
    int width_ = 150;
    int x_;
    int y_;

};

#endif // INVENTORY_H
