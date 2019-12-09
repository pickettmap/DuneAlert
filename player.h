#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QKeyEvent>
#include <QSet>
#include <QPointF>
#include "item.h"
#include "inventory.h"
#include <QObject>

struct Bounds {
    int x1;
    int y1;
    int x2;
    int y2;
};

class player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    player(QPixmap &pixmap, int health, int damage, Bounds b, int gold);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool checkBounds(int, int);
    void changeHealth(int);
    void addItem(Item);
    void TakeDamage(int damage);
    void useItem(int index);
    int getDamage() {return damage_;}
    void setDamage(int change) {damage_ += change; }
    //should this also increase current health?
    void setMaxHealth(int change) { health_ += change;}

    Inventory * getInventory(){return inventory_;}
    bool isDead();

    void changeGold(int change);
    int getGold() { return gold_; }
    void setBound(Bounds b) {bound_ = b; }

int health_;
int current_health_;
int damage_;
int def_;
Bounds bound_;
Inventory * inventory_;
int gold_;
int speed_ = 10;

signals:
    void HealthChanged(int amount);
    void PlayerDied();

private:
    double xprev_;
    double yprev_;

    QSet<int> keysPressed;
};

#endif // PLAYER_H
