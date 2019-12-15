#ifndef SECONDPLAYER_H
#define SECONDPLAYER_H

#include "player.h"


class SecondPlayer: public Player
{
public:
    SecondPlayer(QPixmap &pixmap, int health, int damage, Bounds b, int gold);

public slots:
    void onKeyPressed(QKeyEvent *event);
    void MoveCharacter();
    void CreateInventory();
};

#endif // SECONDPLAYER_H
