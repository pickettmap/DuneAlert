#include "computerplayer.h"
#include "gameview.h"
#include <QDebug>
#include <random>

/*
Function: Computer player constructor
Params: QPixmap &pixmap, int health, int damage, Bounds b, int gold
Desc: Child of Player class. Passes parameters into parent constructor
Returns: ComputerPlayer
*/
ComputerPlayer::ComputerPlayer(QPixmap &pixmap, int health, int damage, Bounds b, int gold)
    : Player(pixmap, health, damage, b, gold)
{
    //connect(timer_, &QTimer::timeout, this, &ComputerPlayer::moveCharacter());
    //timer_.start(1000);
}

/*
Function: moveCharacter
Params: None
Desc: Moves character in a random direction by 15 px
Returns: None
*/
void ComputerPlayer::MoveCharacter() {
    int STEP_SIZE = 15;
    int num = rand() % 8;
    //if only 1 key is being pressed, simply move in that direction
        switch (num){
        case 0:
            if (x() + STEP_SIZE > bound_.x2) {
                return;
            }
            setPos(x()+STEP_SIZE,y());
            break;
        case 1:
            if (x() - STEP_SIZE < bound_.x1) {
                return;
            }
            setPos(x()-STEP_SIZE,y());
            break;
        case 2:
            if (y() - STEP_SIZE < bound_.y1) {
                return;
            }
            setPos(x(),y()-STEP_SIZE);
            break;
        case 3:
            if (y() + STEP_SIZE > bound_.y2) {
                return;
            }
            setPos(x(),y()+STEP_SIZE);
            break;
        case 4:
            if (y() - STEP_SIZE < bound_.y1 || x() + STEP_SIZE > bound_.x2){
                return;
            }
            setPos(x()+STEP_SIZE,y()-STEP_SIZE);
            break;
        case 5:
            if (y() - STEP_SIZE < bound_.y1 || x() - STEP_SIZE < bound_.x1){
                return;
            }
            setPos(x()-STEP_SIZE,y()-STEP_SIZE);
            break;
        case 6:
            if (y() + STEP_SIZE > bound_.y2 || x() + STEP_SIZE > bound_.x2){
                return;
            }
            setPos(x()+STEP_SIZE,y()+STEP_SIZE);
            break;
        case 7:
            if (y() + STEP_SIZE > bound_.y2 || x() - STEP_SIZE < bound_.x1){
                return;
            }
            setPos(x()-STEP_SIZE,y()+STEP_SIZE);
            break;
        default:
            return;
        }
    CheckCollision();
}
