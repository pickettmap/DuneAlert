#ifndef SECONDPLAYER_H
#define SECONDPLAYER_H

#include "player.h"


class SecondPlayer: public player
{
public:
    SecondPlayer(QPixmap &pixmap, int health, int damage, Bounds b, int gold);

public slots:
    void onKeyPressed(QKeyEvent *event);
    void moveCharacter();
};

#endif // SECONDPLAYER_H
