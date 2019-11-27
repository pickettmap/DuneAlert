#include "player.h"
#include <QDebug>

player::player(QPixmap &pixmap, int health, int damage): QObject(), QGraphicsPixmapItem(pixmap)
{
    xprev_ = pos().x();
    yprev_ = pos().y();
    this->health = health;
    this->damage = damage;
}

void player::keyPressEvent(QKeyEvent *event){
    if(
        event->key() == Qt::Key_W ||
        event->key() == Qt::Key_A ||
        event->key() == Qt::Key_S ||
        event->key() == Qt::Key_D
       )
    {
        keysPressed.insert(event->key());
    }

    int STEP_SIZE = 10;

    //if only 1 key is being pressed, simply move in that direction
    if (keysPressed.size() == 1){
        switch (event->key()){
        case Qt::Key_D:
            setPos(x()+STEP_SIZE,y());
            break;
        case Qt::Key_A:
            setPos(x()-STEP_SIZE,y());
            break;
        case Qt::Key_W:
            setPos(x(),y()-STEP_SIZE);
            break;
        case Qt::Key_S:
            setPos(x(),y()+STEP_SIZE);
            break;
        }
    }

    //if two keys are being pressed, move diagonally
    if (keysPressed.size() > 1){

        // up right
        if (keysPressed.contains(Qt::Key_W) && keysPressed.contains(Qt::Key_D)){
            setPos(x()+STEP_SIZE,y()-STEP_SIZE);
        }
        // up left
        if (keysPressed.contains(Qt::Key_W) && keysPressed.contains(Qt::Key_A)){
            setPos(x()-STEP_SIZE,y()-STEP_SIZE);
        }
        // down right
        if (keysPressed.contains(Qt::Key_S) && keysPressed.contains(Qt::Key_D)){
            setPos(x()+STEP_SIZE,y()+STEP_SIZE);
        }
        // down left
        if (keysPressed.contains(Qt::Key_S) && keysPressed.contains(Qt::Key_A)){
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
