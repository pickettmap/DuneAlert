#ifndef SECONDPLAYER_H
#define SECONDPLAYER_H

#include "player.h"


class SecondPlayer: public player
{
public:
    SecondPlayer(QPixmap &pixmap, int health, int damage, Bounds b, int gold);
public slots:
    virtual void onKeyPressed(QKeyEvent *event);
};

#endif // SECONDPLAYER_H
