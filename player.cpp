#include "player.h"
#include "gameview.h"
#include <QDebug>
#include <inventory.h>
#include "burger.h"
#include "toilet.h"
#include "monsterfactory.h"
#include "tutu.h"
#include "gun.h"
/*
Function: Player Constructor
Params: pixmap, health damage, bounds, gold
Desc: Instantiates a player class, starts the timer for player movement
Returns: none
*/
Player::Player(QPixmap &pixmap, int health, int damage, Bounds b, int gold): QObject(), QGraphicsPixmapItem(pixmap)
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
    //Every 50 ms move in the direction of the currenly pressed keys.
    QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(MoveCharacter()));
        timer->start(50); //time specified in ms
}

/*
Function: useItem
Params: int id, item to consume
Desc: Given an item id, uses an item and removes it from player inventory.
Returns: none
*/
void Player::UseItem(int id) {
    Item * i = inventory_->GetItem(id);
    if (i) {
        i->Use(this);
        inventory_->RemoveItem(id);
    }

}

/*
Function: onKeyPressed
Params: QKeyEvent, key that was pressed
Desc: When w/a/s/d is pressed, function adds key to currently pressed keys vector.
Returns: none
*/
void Player::onKeyPressed(QKeyEvent *event){
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

/*
Function: cter
Params: none
Desc: Moves character based on which of its keys are currently pressed
Returns: none
*/
void Player::MoveCharacter() {
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

/*
Function: CheckCollision
Params: none
Desc: Checks around the player to see if any items are colliding, and reacts to appropriate items accordingly.
Returns: none
*/
void Player::CheckCollision() {
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
                        EnemyType arr[4] = {EnemyType::DweebFish, EnemyType::LesserDog, EnemyType::Canary, EnemyType::Helix};
//                        Enemy * e = MonsterFactory::GetEnemy(arr[rand()%4]);
                        Enemy * e = MonsterFactory::GetEnemy(EnemyType::Helix);
                        game.SwitchToUnderWorld(this, e);
                        return;
                    }
                    else if(random>=30 && random < 50)
                    {
                        Burger *tmp1 = new Burger();
                        inventory_->AddItem(tmp1, false);
                    }
                    else if(random >=50 && random < 60)
                    {
                        Gun *gun = new Gun();
                        Tutu *tutu = new Tutu();
                        Item* arr[2] = {gun, tutu};
                        int random2 = rand()%2;
                        inventory_->AddItem(arr[random2],false);
                        arr[random2]->Use(this);
                    }
                    else if(random >= 60 && random < 90)
                    {
                        changeGold(5);
                    }
                    else
                    {
                        int arr[2] = {-1,5};
                        changeHealth(arr[rand()%2]);
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

/*
Function: ChangeHealth
Params: int change, change in health
Desc: Given an amount to change health by, changes the health and emits events to alert other objects of this change.
Returns: none
*/

void Player::changeHealth(int change) {
    //If the addition of health goes above threshhold, set health to threshhold
    if (current_health_ + change > health_) {
        change = health_ - current_health_;
        current_health_ = health_;
    } else {
        current_health_ += change;
    }
    emit StatsUpdated(health_, current_health_, gold_, damage_);
    emit HealthChanged(change);
    if (IsDead()) {
        emit PlayerDied();
    }
}

/*
Function: isDead
Params: none
Desc: Checks if a player's health has gone below 0.
Returns: Bool if player is dead/not dead
*/
bool Player::IsDead() {
    if (current_health_ <= 0) {
        return true;
    }
    return false;
}

/*
Function: changeGold
Params: int amount changed
Desc: Sets gold to the changed amount and tells the stats to update
Returns: none
*/
void Player::changeGold(int amount) {
    gold_ += amount;
    emit StatsUpdated(health_, current_health_, gold_, damage_);
}

/*
Function: onKeyRelease
Params: QKeyEvent, key released
Desc: Removes a key from the keyPressed array if a key was pressed
Returns: none
*/
void Player::onKeyRelease(QKeyEvent *event)
{
    keysPressed.remove(event->key());
}

/*
Function: setMaxHealth
Params: int change, amount health changed
Desc: changes the maximum health value by the number provided, updates stats
Returns: none
*/
void Player::setMaxHealth(int change) {
    health_ += change;
    emit StatsUpdated(health_, current_health_, gold_, damage_);
}

/*
Function: setDamage
Params: int change, amount damage changed
Desc: changes the damage value by the number provided, updates stats
Returns: none
*/
void Player::setDamage(int change) {
    damage_ += change;
    emit StatsUpdated(health_, current_health_, gold_, damage_);
}
