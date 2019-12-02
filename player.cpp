#include "player.h"
#include <QDebug>

player::player(QPixmap &pixmap, int health, int damage, Bounds b): QObject(), QGraphicsPixmapItem(pixmap)
{
    xprev_ = pos().x();
    yprev_ = pos().y();
    this->health = health;
    this->damage = damage;
    bound = b;
}

void player::keyPressEvent(QKeyEvent *event){

    int STEP_SIZE = 10;

    if(
        event->key() == Qt::Key_W ||
        event->key() == Qt::Key_A ||
        event->key() == Qt::Key_S ||
        event->key() == Qt::Key_D
       )
    {
        keysPressed.insert(event->key());
    }

    //if only 1 key is being pressed, simply move in that direction
    if (keysPressed.size() == 1){
        switch (event->key()){
        case Qt::Key_D:
            if (x() + STEP_SIZE > bound.x2) {
                return;
            }
            setPos(x()+STEP_SIZE,y());
            break;
        case Qt::Key_A:
            if (x() - STEP_SIZE < bound.x1) {
                return;
            }
            setPos(x()-STEP_SIZE,y());
            break;
        case Qt::Key_W:
            if (y() - STEP_SIZE < bound.y1) {
                return;
            }
            setPos(x(),y()-STEP_SIZE);
            break;
        case Qt::Key_S:
            if (y() + STEP_SIZE > bound.y2) {
                return;
            }
            setPos(x(),y()+STEP_SIZE);
            break;
        }
    }

    //if two keys are being pressed, move diagonally
    if (keysPressed.size() > 1){

        // up right
        if (keysPressed.contains(Qt::Key_W) && keysPressed.contains(Qt::Key_D)){
            if (y() - STEP_SIZE < bound.y1 || x() + STEP_SIZE > bound.x2){
                return;
            }
            setPos(x()+STEP_SIZE,y()-STEP_SIZE);
        }
        // up left
        if (keysPressed.contains(Qt::Key_W) && keysPressed.contains(Qt::Key_A)){
            if (y() - STEP_SIZE < bound.y1 || x() - STEP_SIZE < bound.x1){
                return;
            }
            setPos(x()-STEP_SIZE,y()-STEP_SIZE);
        }
        // down right
        if (keysPressed.contains(Qt::Key_S) && keysPressed.contains(Qt::Key_D)){
            if (y() + STEP_SIZE > bound.y2 || x() + STEP_SIZE > bound.x2){
                return;
            }
            setPos(x()+STEP_SIZE,y()+STEP_SIZE);
        }
        // down left
        if (keysPressed.contains(Qt::Key_S) && keysPressed.contains(Qt::Key_A)){
            if (y() + STEP_SIZE > bound.y2 || x() - STEP_SIZE < bound.x1){
                return;
            }
            setPos(x()-STEP_SIZE,y()+STEP_SIZE);
        }
    }


    xprev_ = pos().x();
    yprev_ = pos().y();
}

void player::keyReleaseEvent(QKeyEvent *event)
{
    keysPressed.remove(event->key());
}
/*
 * Function: checkBounds
 * Desc: Checks if a move would put the player out of its allowed movement space
 * Params: Bound to check against and position to be moved
 * Returns: Boolean on whether or not move is valid
*/

bool player::checkBounds(int bound, int position) {
    return true;
}
