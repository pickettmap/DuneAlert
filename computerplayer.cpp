#include "computerplayer.h"
#include "gameview.h"
#include <QDebug>

ComputerPlayer::ComputerPlayer(QPixmap &pixmap, int health, int damage, Bounds b, int gold)
    : player(pixmap, health, damage, b, gold)
{
    //connect(timer_, &QTimer::timeout, this, &ComputerPlayer::moveCharacter());
    //timer_.start(1000);
}

void ComputerPlayer::moveCharacter()
{
    qDebug()<<":)";
}
