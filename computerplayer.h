#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "player.h"

class ComputerPlayer : public player
{
public:
    ComputerPlayer(QPixmap &pixmap, int health, int damage, Bounds b, int gold);
};

#endif // COMPUTERPLAYER_H
