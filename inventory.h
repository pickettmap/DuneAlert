#ifndef INVENTORY_H
#define INVENTORY_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>
#include "item.h"
#include "containingbox.h"
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
    void PopupText(Item*);

    void setPos(int x, int y);
    void setDisplay(){displayed_=!displayed_;}
    bool getDisplay(){return displayed_;}

public slots:
    void clearPopup(ContainingBox *box);


private:
    QTimer *timer_ = new QTimer(this);
    int width_ = 150;
    int x_ = 20;
    int y_ = 20;
    std::vector<Item*> consumable_items_;
    std::vector<Item*> equipable_items_;
    bool displayed_ = false;

};

#endif // INVENTORY_H
