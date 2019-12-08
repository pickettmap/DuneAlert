#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QKeyEvent>
#include <QSet>
#include <QPointF>
#include "item.h"
#include "inventory.h"

struct Bounds {
    int x1;
    int y1;
    int x2;
    int y2;
};

class player : public QObject, public QGraphicsPixmapItem
{
public:
    player(QPixmap &pixmap, int health, int damage, Bounds b);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool checkBounds(int, int);
    void changeHealth(int);
    void addItem(Item);
    void TakeDamage(int damage);

    Inventory * getInventory(){return inventory_;}
    bool isDead();

    void changeGold(int change);

int health_;
int current_health_;
int damage_;
Bounds bound_;
Inventory * inventory_;
int gold_;


private:
    double xprev_;
    double yprev_;

    QSet<int> keysPressed;
};

#endif // PLAYER_H
