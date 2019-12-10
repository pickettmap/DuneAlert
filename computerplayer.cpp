#include "computerplayer.h"
#include "gameview.h"
#include <QDebug>

ComputerPlayer::ComputerPlayer(QPixmap &pixmap, int health, int damage, Bounds b, int gold)
    : player(pixmap, health, damage, b, gold)
{
}

void ComputerPlayer::moveCharacter()
{
    GameView &game = GameView::GetInstance();

}
