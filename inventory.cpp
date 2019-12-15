#include "inventory.h"
#include "player.h"
#include "gameview.h"
#include "containingbox.h"
#include <QPainter>
#include <item.h>
#include <QDebug>

Inventory::Inventory(QColor color)
{
    color_ = color;
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
Desc: Draws the inventory
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
    //For each consumable item, write the correct description and add it to the inventory
    if (consumable_items_.size() > 0){
        current_y += distance_between;
        painter->drawText(QPoint(shifted_x, current_y), "Consumables:");
        for(size_t i = 0; i < consumable_items_.size(); i ++) {
            current_y += distance_between;
            QString desc = QString::fromStdString(consumable_items_[i]->getDescription());
            QString name = QString::fromStdString("[" + std::to_string(i + 1) + "] " + consumable_items_[i]->getName()) + ": " + desc;
            painter->drawText(QPoint(shifted_x, current_y), name);
        }
    }
    //For each equipable item, write the correct description and add it to the inventory.
    if (equipable_items_.size() > 0) {
    current_y += distance_between;
    painter->drawText(QPoint(shifted_x, current_y), "Equipped:");
        for(size_t i = 0; i < equipable_items_.size(); i ++) {
            current_y += distance_between;
            QString desc = QString::fromStdString(equipable_items_[i]->getDescription());
            QString name = QString::fromStdString(equipable_items_[i]->getName()) + ": " + desc;
            painter->drawText(QPoint(shifted_x, current_y), name);

        }
    }
    painter->setPen(color_);
    painter->drawRect(QRect(this->x_, this->y_, this-> width_, height));
    painter->setBrush(b);
}

/*
Function: setPos
Params: int x, int y
Desc: Given points, set inventory to that point.
Returns: none
*/
void Inventory::setPos(int x, int y) {
    x_ = x;
    y_ = y;
}

/*
Function: GetItem
Params: int id, item id
Desc: Given an item id, returns a pointer to the correct item
Returns: pointer to item
*/
Item * Inventory::GetItem(int id) {
    if (id < consumable_items_.size() && id >=0) {
    return consumable_items_[id];
    }
    return nullptr;
}

/*
Function: RemoveItem
Params: int id
Desc: Given an item id, remove that item from the inventory.
Returns: none
*/
void Inventory::RemoveItem(int id) {
    consumable_items_.erase(consumable_items_.begin() + id);
}

/*
Function: AddItem
Params: Item, bool underworld
Desc: Adds an item to the players inventory
Returns: none
*/
void Inventory::AddItem(Item *item, bool underworld)
{
//    PopupText(item, underworld);
    if (item->getItemType() == itemtype::Consumable) {
        consumable_items_.push_back(item);
        QString q = QString::fromStdString(item->getName());
        //qDebug() << q;
    } else {
        equipable_items_.push_back(item);
    }
}

/*
Function: PopupText
Params: Item to be described
Desc: Given an item, creates a popup text that describes the item received
Returns: none
*/
void Inventory::PopupText(Item *item, bool underworld)
{
    if (underworld) {
        return;
    }
    GameView &game = GameView::GetInstance();
    std::string text= "You got a(n) " + item->getName() + ". " + item->getDescription();
    ContainingBox *box = new ContainingBox(0,game.scene->height(),game.scene->width(),300,Qt::GlobalColor::white, text);
    game.scene->addItem(box);

    QTimer::singleShot(1000,[=](){
        clearPopup(box);
    });
}

/*
Function: clearPopup
Params: Containingbox
Desc: Removes given box from the scene
Returns: none
*/
void Inventory::clearPopup(ContainingBox *box)
{
    //timer_->stop();
    GameView &game = GameView::GetInstance();
    if (!game.switching_to_underworld_){
     game.scene->removeItem(box);
    }
}
