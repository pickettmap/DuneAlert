#include "secondplayer.h"
#include "gameview.h"
#include <QDebug>

SecondPlayer::SecondPlayer(QPixmap &pixmap, int health, int damage, Bounds b, int gold)
    : player(pixmap, health, damage, b, gold)
{

}

void SecondPlayer::onKeyPressed(QKeyEvent *event){
    GameView& game = GameView::GetInstance();
    int STEP_SIZE = 10;
    qDebug() << event->key();
    if(event->key() == Qt::Key_Escape)
    {

        inventory_->setPos(100,100);
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

    qDebug() << keysPressed.size();
    //if only 1 key is being pressed, simply move in that direction
    if (keysPressed.size() == 1){
        switch (event->key()){
        case Qt::Key_Right:
            qDebug() << "test";
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

//    handling interacting with items in overworld
//    QList <QGraphicsItem *> colliding_items = collidingItems();
//    for (int i = 0, n = colliding_items.size(); i < n; i++)
//    {
//        if (dynamic_cast<Item*>(colliding_items[i])){
//            Item* item = dynamic_cast<Item *>(colliding_items[i]);
//            if(item->getItemType()==itemtype::Scenery)
//            {
//                game.scene->removeItem(item);
//            }
//            else if (item->getItemType()==itemtype::Consumable)
//            {
//                inventory_->AddItem(item);
//                qDebug() << "test";
//                game.scene->removeItem(item);
//            }
//            else if (item->getItemType()==itemtype::Equipable) {
//                inventory_->AddItem(item);
//                //Equipable items are used immedietely
//                item->Use(this);
//                game.scene->removeItem(item);
//            }
//        }
//    }


    xprev_ = pos().x();
    yprev_ = pos().y();
    game.scene->update();
}
