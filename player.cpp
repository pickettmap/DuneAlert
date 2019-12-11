#include "player.h"
#include "gameview.h"
#include <QDebug>
#include <inventory.h>
#include "burger.h"
#include "toilet.h"
#include "monsterfactory.h"
#include "tutu.h"

player::player(QPixmap &pixmap, int health, int damage, Bounds b, int gold): QObject(), QGraphicsPixmapItem(pixmap)
{
    xprev_ = pos().x();
    yprev_ = pos().y();
    health_ = health;
    damage_ = damage;
    current_health_ = health;
    health_ = health;
    bound_ = b;
    inventory_ = new Inventory();
    inventory_->setVisible(false);

    display_ = new StatsDisplay(200,200,"Player 1", getMaxHealth(),health, gold,damage, Qt::GlobalColor::blue);
    display_->setVisible(false);

    gold_ = gold;
    QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(moveCharacter()));
        timer->start(50); //time specified in ms
}

void player::useItem(int id) {
    Item * i = inventory_->GetItem(id);
    if (i) {
        i->Use(this);
        inventory_->RemoveItem(id);
    }

}

void player::onKeyPressed(QKeyEvent *event){
    GameView& game = GameView::GetInstance();
    if(event->key() == Qt::Key_Escape)
    {
        if(inventory_->getDisplay())
        {
            inventory_->setVisible(true);
            display_->setVisible(true);
        }
        else
        {
            inventory_->setVisible(false);
            display_->setVisible(false);
        }
        game.scene->update();
        inventory_->setDisplay();
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

    game.scene->update();
}

void player::moveCharacter() {
    GameView &game = GameView::GetInstance();
    if (game.switching_to_underworld_ || game.switching_to_overworld_) {
        return;
    }
    int STEP_SIZE = 15;
    if (keysPressed.size() == 1){
        switch (*keysPressed.begin()){
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
    CheckCollision();
}

void player::CheckCollision() {
    GameView& game = GameView::GetInstance();
    QList <QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if (dynamic_cast<Item*>(colliding_items[i])){
            Item* item = dynamic_cast<Item *>(colliding_items[i]);
            if(item->getItemType()==itemtype::Scenery)
            {
                Toilet *tmp = (Toilet*)(item);
                if(!tmp->getFlush())
                {
                    int random = rand()%100;
                    if(random<30)
                    {
                        Enemy * e = MonsterFactory::GetEnemy(EnemyType::DweebFish);
                        game.SwitchToUnderWorld(this, e);
                        return;
                    }
                    else
                    {
                        Burger *tmp1 = new Burger();
                        inventory_->AddItem(tmp1, false);
                    }
                    tmp->Flush();
                }
                setPos(xprev_,yprev_);
                return;
            }
            else if (item->getItemType()==itemtype::Consumable)
            {
                inventory_->AddItem(item, false);
                game.scene->removeItem(item);
            }
            else if (item->getItemType()==itemtype::Equipable) {
                inventory_->AddItem(item, false);
                //Equipable items are used immedietely
                item->Use(this);
                game.scene->removeItem(item);
            }
        }
    }

    xprev_=pos().x();
    yprev_=pos().y();
}

void player::changeHealth(int change) {
    //If the addition of health goes above threshhold, set health to threshhold
    if (current_health_ + change > health_) {
        current_health_ = health_;
    } else {
        current_health_ += change;
    }
    emit StatsUpdated(health_, current_health_, gold_, damage_);
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
    gold_ += amount;
    emit StatsUpdated(health_, current_health_, gold_, damage_);
}

void player::onKeyRelease(QKeyEvent *event)
{
    keysPressed.remove(event->key());
}

void player::setMaxHealth(int change) {
    health_ += change;
    emit StatsUpdated(health_, current_health_, gold_, damage_);
}

void player::setDamage(int change) {
    damage_ += change;
    emit StatsUpdated(health_, current_health_, gold_, damage_);
}
