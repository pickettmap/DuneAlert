#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QKeyEvent>
#include <QSet>
#include <QPointF>

class player : public QObject, public QGraphicsPixmapItem
{
public:
    player(QPixmap &pixmap);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    double xprev_;
    double yprev_;

    QSet<int> keysPressed;
};

#endif // PLAYER_H
