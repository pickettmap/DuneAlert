#include "player.h"
#include "gameview.h"
#include <QDebug>
#include <inventory.h>

player::player(QPixmap &pixmap, int health, int damage, Bounds b, int gold): QObject(), QGraphicsPixmapItem(pixmap)
{
    xprev_ = pos().x();
    yprev_ = pos().y();
    this->health_ = health;
    this->damage_ = damage;
    current_health_ = health;
    health_ = health;
    bound_ = b;
    inventory_ = new Inventory();
    inventory_->setVisible(false);
    gold_ = gold;
}

void player::useItem(int id) {
    Item * i = inventory_->GetItem(id);
    if (i) {
        i->Use(this);
        inventory_->RemoveItem(id);
    }

}

void player::keyPressEvent(QKeyEvent *event){
    GameView& game = GameView::GetInstance();
    int STEP_SIZE = 10;

    if(event->key() == Qt::Key_Escape)
    {

        inventory_->setPos(100,100);
        inventory_->setVisible(true);
        game.scene->update();
    }

    //handling player movement
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


    //handling interacting with items in overworld
    QList <QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if (dynamic_cast<Item*>(colliding_items[i])){
            Item* item = dynamic_cast<Item *>(colliding_items[i]);
            if(item->getItemType()==itemtype::Scenery)
            {
                game.scene->removeItem(item);
            }
            else if (item->getItemType()==itemtype::Consumable)
            {
                inventory_->AddItem(item);
                game.scene->removeItem(item);
            }
        }
    }

    xprev_ = pos().x();
    yprev_ = pos().y();
    game.scene->update();
}

void player::changeHealth(int change) {
    current_health_ += change;
    emit HealthChanged(change);
    if (isDead()) {
        emit PlayerDied();
    }
}

bool player::isDead() {
    if (current_health_ <= 0) {
        return true;
    }
    return false;
}

void player::changeGold(int amount) {
    gold_ -= amount;
}

void player::keyReleaseEvent(QKeyEvent *event)
{
    keysPressed.remove(event->key());
}
