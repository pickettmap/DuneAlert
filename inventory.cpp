#include "inventory.h"
#include <QPainter>
#include <item.h>

Inventory::Inventory(int x, int y)
{
    x_ = x;
    y_ = y;
    Item *it;
    Item *pt;
    items.push_back(it);
    items.push_back(pt);
}

QRectF Inventory::boundingRect() const
{
    int height = int(items.size()) * 30;
    return QRectF(x_,y_, width_, height);
}

/*
Coded By: Mikayla Pickett
Function: shape
Params: none
Desc: sets graph as square
Returns: QPainterPath
*/
QPainterPath Inventory::shape() const
{
    int height = int(items.size()) * 30;
    QPainterPath path;
    path.addRect(x_,y_,width_,height);
    return path;
}

/*
Coded By: Mikayla Pickett
Function: Paint
Params: QPainter, QStyleOptionGraphicsItem, QWidget
Desc: allows cell to be drawn
Returns: void
*/
void Inventory::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int height = int(items.size()) * 30;
    QBrush b = painter->brush();
    painter->setPen(Qt::GlobalColor::white);
    painter->drawText(QPoint(this->x_, this->y_), "Inventory");
    for(size_t i = 0; i < items.size(); i ++) {
        painter->drawText(QPoint(this->x_ + 10, this->y_ + (i + 1) * 30 - 15), "Item - 20 Damage");
    }
    painter->drawRect(QRect(this->x_, this->y_, this-> width_, height));
    painter->setBrush(b);
}
