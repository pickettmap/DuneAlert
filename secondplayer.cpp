#include "secondplayer.h"
#include "gameview.h"
#include <QDebug>

SecondPlayer::SecondPlayer(QPixmap &pixmap, int health, int damage, Bounds b, int gold)
    : player(pixmap, health, damage, b, gold)
{
    xprev_ = pos().x();
    yprev_ = pos().y();
    inventory_ = new Inventory();
    inventory_->setVisible(false);
}

void SecondPlayer::onKeyPressed(QKeyEvent *event){
    GameView &game = GameView::GetInstance();
    if(event->key() == Qt::Key_Control)
    {
        inventory_->setVisible(true);
        game.scene->update();
    }

    //handling player movement
    if(
        event->key() == Qt::Key_Up ||
        event->key() == Qt::Key_Left ||
        event->key() == Qt::Key_Down ||
        event->key() == Qt::Key_Right
       )
    {
        keysPressed.insert(event->key());
    }
}

void SecondPlayer::moveCharacter() {
    int STEP_SIZE = 15;
    //if only 1 key is being pressed, simply move in that direction
    if (keysPressed.size() == 1){
        switch (* keysPressed.begin()){
        case Qt::Key_Right:
            if (x() + STEP_SIZE > bound_.x2) {
                return;
            }
            setPos(x()+STEP_SIZE,y());
            break;
        case Qt::Key_Left:
            if (x() - STEP_SIZE < bound_.x1) {
                return;
            }
            setPos(x()-STEP_SIZE,y());
            break;
        case Qt::Key_Up:
            if (y() - STEP_SIZE < bound_.y1) {
                return;
            }
            setPos(x(),y()-STEP_SIZE);
            break;
        case Qt::Key_Down:
            if (y() + STEP_SIZE > bound_.y2) {
                return;
            }
            setPos(x(),y()+STEP_SIZE);
            break;
        }
    }

//    if two keys are being pressed, move diagonally
    if (keysPressed.size() > 1){

        // up right
        if (keysPressed.contains(Qt::Key_Up) && keysPressed.contains(Qt::Key_Right)){
            if (y() - STEP_SIZE < bound_.y1 || x() + STEP_SIZE > bound_.x2){
                return;
            }
            setPos(x()+STEP_SIZE,y()-STEP_SIZE);
        }
        // up left
        if (keysPressed.contains(Qt::Key_Up) && keysPressed.contains(Qt::Key_Left)){
            if (y() - STEP_SIZE < bound_.y1 || x() - STEP_SIZE < bound_.x1){
                return;
            }
            setPos(x()-STEP_SIZE,y()-STEP_SIZE);
        }
        // down right
        if (keysPressed.contains(Qt::Key_Down) && keysPressed.contains(Qt::Key_Right)){
            if (y() + STEP_SIZE > bound_.y2 || x() + STEP_SIZE > bound_.x2){
                return;
            }
            setPos(x()+STEP_SIZE,y()+STEP_SIZE);
        }
        // down left
        if (keysPressed.contains(Qt::Key_Down) && keysPressed.contains(Qt::Key_Left)){
            if (y() + STEP_SIZE > bound_.y2 || x() - STEP_SIZE < bound_.x1){
                return;
            }
            setPos(x()-STEP_SIZE,y()+STEP_SIZE);
        }
    }

    CheckCollision();
}
