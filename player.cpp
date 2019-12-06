#include "player.h"
#include "gameview.h"
#include <QDebug>

player::player(QPixmap &pixmap, int health, int damage, Bounds b): QObject(), QGraphicsPixmapItem(pixmap)
{
    xprev_ = pos().x();
    yprev_ = pos().y();
    this->health_ = health;
    this->damage_ = damage;
    current_health_ = health;
    bound_ = b;
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
            if (x() + STEP_SIZE > bound_.x2) {
                return;
            }
            setPos(x()+STEP_SIZE,y());
            break;
        case Qt::Key_A:
            if (x() - STEP_SIZE < bound_.x1) {
                return;
            }
            setPos(x()-STEP_SIZE,y());
            break;
        case Qt::Key_W:
            if (y() - STEP_SIZE < bound_.y1) {
                return;
            }
            setPos(x(),y()-STEP_SIZE);
            break;
        case Qt::Key_S:
            if (y() + STEP_SIZE > bound_.y2) {
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
            if (y() - STEP_SIZE < bound_.y1 || x() + STEP_SIZE > bound_.x2){
                return;
            }
            setPos(x()+STEP_SIZE,y()-STEP_SIZE);
        }
        // up left
        if (keysPressed.contains(Qt::Key_W) && keysPressed.contains(Qt::Key_A)){
            if (y() - STEP_SIZE < bound_.y1 || x() - STEP_SIZE < bound_.x1){
                return;
            }
            setPos(x()-STEP_SIZE,y()-STEP_SIZE);
        }
        // down right
        if (keysPressed.contains(Qt::Key_S) && keysPressed.contains(Qt::Key_D)){
            if (y() + STEP_SIZE > bound_.y2 || x() + STEP_SIZE > bound_.x2){
                return;
            }
            setPos(x()+STEP_SIZE,y()+STEP_SIZE);
        }
        // down left
        if (keysPressed.contains(Qt::Key_S) && keysPressed.contains(Qt::Key_A)){
            if (y() + STEP_SIZE > bound_.y2 || x() - STEP_SIZE < bound_.x1){
                return;
            }
            setPos(x()-STEP_SIZE,y()+STEP_SIZE);
        }
    }

    GameView& game = GameView::GetInstance();

    QList <QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        Item* item = dynamic_cast<Item *>(colliding_items[i]);
        if(item != nullptr)
        {
            inventory_.push_back(item);
            game.scene->removeItem(item);
        }
    }

    xprev_ = pos().x();
    yprev_ = pos().y();
}

void player::changeHealth(int change) {
    current_health_ += change;
    //TODO ZL Add function that checks if this outright kills them.
}

bool player::isDead() {
    if (current_health_ <= 0) {
        return true;
    }
    return false;
}

void player::keyReleaseEvent(QKeyEvent *event)
{
    keysPressed.remove(event->key());
}
