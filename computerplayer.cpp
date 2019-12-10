#include "computerplayer.h"
#include "gameview.h"

ComputerPlayer::ComputerPlayer(QPixmap &pixmap, int health, int damage, Bounds b, int gold)
    : player(pixmap, health, damage, b, gold)
{

}
