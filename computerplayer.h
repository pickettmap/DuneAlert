#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <QTimer>
#include "player.h"

class ComputerPlayer : public player
{
public:
    ComputerPlayer(QPixmap &pixmap, int health, int damage, Bounds b, int gold);
public slots:
    void moveCharacter();

private:
    QTimer timer_;
};

#endif // COMPUTERPLAYER_H
