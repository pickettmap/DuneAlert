#ifndef UNDERWORLDPLAYER_H
#define UNDERWORLDPLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QSet>
#include "player.h"

class UnderworldPlayer : public QObject, public QGraphicsPixmapItem
{
public:
    UnderworldPlayer(QPixmap &pixmap);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    double xprev_;
    double yprev_;

    QSet<int> keysPressed;
};

#endif // UNDERWORLDPLAYER_H
