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
    Inventory(QColor color_);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void AddItem(Item *item, bool underworld);

    Item* GetItem(int index);
    void RemoveItem(int index);
    int GetConsumableItemsCount() { return int(consumable_items_.size());}

    void UseItem();
    void PopupText(Item*, bool underworld);

    void setPos(int x, int y);
    void setDisplay(){displayed_=!displayed_;}
    bool getDisplay(){return displayed_;}

public slots:
    void clearPopup(ContainingBox *box);

private:
    QColor color_;
    int width_ = 200;
    int x_ = 20;
    int y_ = 20;
    std::vector<Item*> consumable_items_;
    std::vector<Item*> equipable_items_;
    bool displayed_ = false;

};

#endif // INVENTORY_H
