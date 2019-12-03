#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QKeyEvent>
#include <QSet>
#include <QPointF>

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

int health;
int current_health;
int damage;
Bounds bound;


private:
    double xprev_;
    double yprev_;

    QSet<int> keysPressed;
};

#endif // PLAYER_H
