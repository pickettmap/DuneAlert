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

    void UpdateInventory();
    void AddItem(Item *item);

    void UseItem();

    void setPos(int x, int y);

    std::vector<Item*> items;

private:
    int width_ = 150;
    int x_ = 20;
    int y_ = 20;

};

#endif // INVENTORY_H
