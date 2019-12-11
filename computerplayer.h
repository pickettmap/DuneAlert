#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <QTimer>
#include <random>
#include "player.h"

class ComputerPlayer : public Player
{
public:
    ComputerPlayer(QPixmap &pixmap, int health, int damage, Bounds b, int gold);
public slots:
    void moveCharacter();

private:
    QTimer timer_;
};

#endif // COMPUTERPLAYER_H
