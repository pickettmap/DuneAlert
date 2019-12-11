#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QKeyEvent>
#include <QSet>
#include <QPointF>
#include "item.h"
#include "inventory.h"
#include "statsdisplay.h"
#include <QObject>

struct Bounds {
    int x1;
    int y1;
    int x2;
    int y2;
};

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Player(QPixmap &pixmap, int health, int damage, Bounds b, int gold);
    bool CheckBounds(int, int);
    void AddItem(Item);
    void TakeDamage(int damage);
    void UseItem(int index);
    //Getters
    int getHealth() { return current_health_; }
    int getMaxHealth() { return health_; }
    int getDamage() {return damage_;}
    int getGold() { return gold_; }
    //Setters
    void setDamage(int change);
    void setMaxHealth(int change);
    void changeGold(int change);
    void changeHealth(int change);
    void setBound(Bounds b) {bound_ = b; }

    Inventory * getInventory(){return inventory_;}
    StatsDisplay * getStats(){return display_;}
    bool IsDead();
    void CheckCollision();



public slots:
    virtual void onKeyPressed(QKeyEvent *event);
    void onKeyRelease(QKeyEvent * event);
    virtual void MoveCharacter();

protected:
    QSet<int> keysPressed;
    double xprev_;
    double yprev_;
    Bounds bound_;
    Inventory * inventory_;
    StatsDisplay *display_;

    int health_;
    int current_health_;
    int damage_;
    int def_;
    int gold_;
    int speed_ = 10;

signals:
    void HealthChanged(int amount);
    void StatsUpdated(int max_health, int current_health, int gold, int damage);
    void PlayerDied();


};

#endif // PLAYER_H
