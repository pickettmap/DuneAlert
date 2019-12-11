#include "computerplayer.h"
#include "gameview.h"
#include <QDebug>
#include <random>


ComputerPlayer::ComputerPlayer(QPixmap &pixmap, int health, int damage, Bounds b, int gold)
    : player(pixmap, health, damage, b, gold)
{
    //connect(timer_, &QTimer::timeout, this, &ComputerPlayer::moveCharacter());
    //timer_.start(1000);
}

void ComputerPlayer::moveCharacter() {
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
