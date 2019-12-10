#include "inventory.h"
#include "player.h"
#include "gameview.h"
#include <QPainter>
#include <item.h>
#include <QDebug>

Inventory::Inventory()
{
}

QRectF Inventory::boundingRect() const
{
    int height = int((consumable_items_.size()) + equipable_items_.size()) * 30;
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
    int height = int((consumable_items_.size()) + equipable_items_.size()) * 30;
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
    int distance_between = 20;
    int height = int((consumable_items_.size()) + equipable_items_.size()) * distance_between + 60;
    QBrush b = painter->brush();
    painter->setPen(Qt::GlobalColor::white);
    painter->drawText(QPoint(this->x_, this->y_), "Inventory");
    int current_y = this->y_;
    int shifted_x = this->x_ + 10;
    if (consumable_items_.size() > 0){
        current_y += distance_between;
        painter->drawText(QPoint(shifted_x, current_y), "Consumables:");
        for(size_t i = 0; i < consumable_items_.size(); i ++) {
            current_y += distance_between;
            QString desc = QString::fromStdString(consumable_items_[i]->getDescription());
            QString name = QString::fromStdString("[" + std::to_string(i + 1) + "] " + consumable_items_[i]->getName()) + " - " + desc;
            painter->drawText(QPoint(shifted_x, current_y), name);
        }
    }

    if (equipable_items_.size() > 0) {
    current_y += distance_between;
    painter->drawText(QPoint(shifted_x, current_y), "Equipped:");
        for(size_t i = 0; i < equipable_items_.size(); i ++) {
            current_y += distance_between;
            QString desc = QString::fromStdString(equipable_items_[i]->getDescription());
            QString name = QString::fromStdString(equipable_items_[i]->getName()) + " - " + desc;
            painter->drawText(QPoint(shifted_x, current_y), name);

        }
    }

    painter->drawRect(QRect(this->x_, this->y_, this-> width_, height));
    painter->setBrush(b);
}

void Inventory::setPos(int x, int y) {
    x_ = x;
    y_ = y;
}

Item * Inventory::GetItem(int id) {
    if (id < consumable_items_.size() && id >=0) {
    return consumable_items_[id];
    }
    return nullptr;
}

void Inventory::RemoveItem(int id) {
    consumable_items_.erase(consumable_items_.begin() + id);
}

void Inventory::AddItem(Item *item)
{
    if (item->getItemType() == itemtype::Consumable) {
        consumable_items_.push_back(item);
        QString q = QString::fromStdString(item->getName());
        qDebug() << q;
    } else {
        equipable_items_.push_back(item);
    }
}
