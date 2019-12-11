#include "underworld.h"
#include <QGraphicsScene>
#include <QPainter>
#include "bullet.h"
#include "containingbox.cpp"
#include "player.h"
#include <QTimer>
#include "enemy.h"
#include <QDebug>
#include "healthbar.h"
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "gameview.h"
#include "inventory.h"


Underworld::Underworld(QGraphicsScene * main_scene)
{
    scene_ = main_scene;
}

/*
Function: DrawUnderworld
Params: Enemy, Player
Desc: Given an enemy and a player to work with, creates necessary assets for the underworld.
Returns: None
*/

void Underworld::DrawUnderworld(Enemy *enemy, player *player) {
    this->enemy_ = enemy;
    this->player_= player;

    //EventHandler

    //Containing box coordinates (temp)

    //containing box width and height
    int cwidth = 300;
    int cheight = 275;

    //starting point for containing box
    cx1_ = scene_->width()/2 - 100;
    cy1_ = scene_->height()/2 - 100;


    //other corner
    cx2_ = cx1_ + cwidth;
    cy2_ = cy1_ + cheight;

    int player_sprite_size = 25;

    //Set Background
    QImage *img = new QImage(":/images/battlebackground.jpg");
    *img = img->scaled(100,100,Qt::KeepAspectRatioByExpanding);
    QBrush bg_brush(*img);
    scene_ ->setBackgroundBrush(bg_brush);

    //DRAW AND POSITION THE PLAYER
    QPixmap sprite = QPixmap(":/images/heart.png");
    sprite = sprite.scaled(player_sprite_size, player_sprite_size,Qt::KeepAspectRatio);
    Bounds bound = {cx1_, cy1_ , cx2_ - player_sprite_size, cy2_ - player_sprite_size};

    player_->setPixmap(sprite);
    player_->setBound(bound);

    //DRAW THE BOX THE PLAYER MAY MOVE AROUND IN
    ContainingBox *b = new ContainingBox(cx1_, cy1_, cwidth, cheight, Qt::GlobalColor::white, "");
    scene_->addItem(b);
    connect(this, &Underworld::OnBulletFired, this, &Underworld::FireBullet);

    //DRAW THE ENEMY

    enemy_->setPos(cx1_,cy1_-enemy_->pixmap().height()-100);
    scene_->addItem(enemy_);

    //Player 1 Health Bar
    HealthBar *ph = new HealthBar(cx1_, cy2_ + 10, cwidth, 20, player_->getMaxHealth(), player_->getHealth());
    scene_->addItem(ph);
    connect(player_, &player::HealthChanged, ph, &HealthBar::ChangeHealth);
    connect(player_, &player::PlayerDied, this, &Underworld::OnPlayerDeath);
    //Health Bar Temporary text

    //Enemy health bar
    HealthBar *eh = new HealthBar(cx1_, cy1_-100, cwidth, 50, enemy_->getMaxHealth(), enemy_->getHealth());
    scene_->addItem(eh);
    connect(this, &Underworld::OnEnemyHit, eh, &HealthBar::ChangeHealth);


    //Draw boxes for options
    fight_box_ = new ContainingBox(cx1_, cy2_ + 50, 150, 50, Qt::GlobalColor::green, "Fight [F]");
    scene_->addItem(fight_box_);


    bribe_box_ = new ContainingBox(cx1_ + 150, cy2_ + 50, 150, 50, Qt::GlobalColor::green, "Bribe [B]");
    scene_->addItem(bribe_box_);

    player_->getInventory()->setPos(-20, 150);
    scene_->addItem(player_->getInventory());

}


/*
Function: ProcessAttackPattern
Params: Vector of Attack Patterns
Desc: Given an instructional list of bullets to fire, fires those bullets.
Returns: none
*/
void Underworld::ProcessAttackPattern(std::vector<AttackPattern> s) {
    for (size_t i = 0; i < s.size(); i ++) {
        QTimer::singleShot(s[i].delay, [=](){
            if (!fight_over_) {
                FireBullet(s[i].x, s[i].y, s[i].dir);
            }
        });
    }
}

/*
Function: FireBullet
Params: x starting x, y starting y, direction to travel in
Desc: Fires a bullet and travels it in that direction until it hits the boundries.
Returns: none
*/
void Underworld::FireBullet(int x, int y, Direction d) {
        Bounds bound = {cx1_ - 10,cy1_ - 10, cx2_ + 10, cx2_ + 10};
        Bullet *b = new Bullet(x, y, d, scene_, bound);
        scene_->addItem(b);
}

/*
Function: OnFightClicked
Params: none
Desc: Carries out an enemies' attack turn and processes damage
Returns: none
*/
void Underworld::OnFightClicked() {
    //Send damage to the enemy and health bars
    emit OnEnemyHit(-1 * player_->getDamage());
    enemy_->changeHealth(-1 * player_->getDamage());
    scene_->update();

    //Check if enemy is dead
    if (enemy_->isDead()) {
        EnemyDeath();
        return;
    }

    InitiateFightSequence();
}

/*
Function: onItemUsed
Params: none
Desc: Uses an item in the player's inventory and applies effects to the fight. Starts enemy attack turn
Returns: none
*/
void Underworld::OnItemUsed() {
    //Check if item kills enemy
    if (enemy_->isDead()) {
        EnemyDeath();
        return;
    }
    scene_->update();
    InitiateFightSequence();
}

/*
Function: InitiateFightSequence
Params: none
Desc: Starts the enemy attack pattern, adding the movable player to the screen and removing some functionality.
Returns:  none
*/
void Underworld::InitiateFightSequence() {
    //If the enemy is dead, don't initiate a fight sequence
    scene_->removeItem(fight_box_);
    scene_->removeItem(bribe_box_);
    fighting_ = true;

    //Add the player to the scene, do health calculations
    player_->setPos(scene_->width()/2+150,scene_->height()/2+130);
    scene_->addItem(player_);
    player_->setFocus();



    //After a 1 second delay, initiate the bullets
    QTimer::singleShot(1000, [=]() {
        ProcessAttackPattern(enemy_->GetFightPattern());
    });

    //After all bullets have been fired plus a few seconds, remove the player from the battle.
    QTimer::singleShot(enemy_->getFightDuration() + 2500, [=] () {
        if(!fight_over_) {
            scene_->addItem(fight_box_);
            scene_->addItem(bribe_box_);
            scene_->removeItem(player_);
            fighting_ = false;
        }
    });
}

/*
Function: SwitchToOverWorld
Params: none
Desc: Removes necessary objects from the underworld and passes control back to the overworld.
Returns: none
*/
void Underworld::SwitchToOverWorld() {
    scene_->clear();
    GameView &game =  GameView::GetInstance();
    Mode mode = game.get_game_mode();
    //Different modes depending on how many people are in the game
    if (mode == SinglePlayer) {
        game.CreateSinglePlayerOverWorld();
    } else if (mode == TwoPlayer) {
        game.CreateTwoPlayerOverWorld();
    }
    //If you delete the underwold object some memory is gonna leak
    delete this;
}

/*
Function: EndBattle
Params: QString s, the string to display in the after message box.
Desc: Displays the after-battle stats and gains, then after a certain time calls switch to overworld.
Returns:  none
*/
void Underworld::EndBattle(QString s) {
    scene_->removeItem(player_->getInventory());
    scene_->clear();
    scene_->update();

    //Draw end game review
    int x = scene_->width()/2 - 200;
    int y = scene_->height()/2 - 200;
    ContainingBox *end = new ContainingBox(x,y, 600, 200, Qt::GlobalColor::white, "");
    QGraphicsTextItem *text = new QGraphicsTextItem(s);
    text->setDefaultTextColor(Qt::GlobalColor::white);
    text->setPos(x+20, y+20);
    //Switches back to overworld in 5 seconds
    QTimer::singleShot(3000, [=]() {
        SwitchToOverWorld();
    });
    scene_->addItem(text);
    scene_->addItem(end);

}

/*
Function: Bribe
Params: none
Desc: Carries out the bribe action, where the player doesn't fight and instead pays a gold premium.
Returns: none
*/
void Underworld::Bribe() {
    player_->changeGold(-10);
    EndBattle("You ran like a coward and lost 10 gold!");

}
/*
Function: EnemyDeath
Params: none
Desc: When the player successfully kills an enemy, the player receives bountiful rewards.
Returns: none
*/
void Underworld::EnemyDeath() {
    fight_over_ = true;
    player_->changeGold(enemy_->getGold());
    std::string message = "You killed " + enemy_->getName() + " and received " + std::to_string(enemy_->getGold()) + " gold. ";

    if (enemy_->getItem()){
        player_->getInventory()->AddItem(enemy_->getItem(), true);
        message += "They were also carrying a " + enemy_->getItem()->getName() + "!";
    }

    QString q = QString::fromStdString(message);


    EndBattle(q);
}
/*
Function: OnKeyPress
Params: QKeyEvent * event, the key the user is pressing
Desc: Given a key press, determines what action the user will take.
Returns: none
*/
void Underworld::OnKeyPress(QKeyEvent *event) {
    if (fighting_)
        return;
    if (event->key() == Qt::Key::Key_F) {
        OnFightClicked();
    }
    else if (event->key() == Qt::Key::Key_B) {
        Bribe();
    }
    else if (event->key() == Qt::Key::Key_1) {
        //I'm not sure if this can be simplified to reduce repeated code
        if (player_->getInventory()->GetConsumableItemsCount() < 1) {
            return;
        }
        player_->useItem(0);
        InitiateFightSequence();
    }
    else if (event->key() == Qt::Key::Key_2) {
        if (player_->getInventory()->GetConsumableItemsCount() < 2) {
            return;
        }
        player_->useItem(1);
        InitiateFightSequence();

    }
    else if (event->key() == Qt::Key::Key_3) {
        if (player_->getInventory()->GetConsumableItemsCount() < 3) {
            return;
        }
        player_->useItem(2);
        InitiateFightSequence();
    }
    scene_->update();
}
/*
Function: OnPlayerDeath
Params: none
Desc: Punishes the player for losing a battle with monitary value.
Returns: none
*/
void Underworld::OnPlayerDeath() {
    fight_over_ = true;
    int lose_amount = -20;
    if(player_->isDead()) {
        scene_->removeItem(player_);
        player_->changeGold(lose_amount);
        player_->changeHealth(5);
    }
    std::string message = "You lost to " + enemy_->getName() + " and lost " + std::to_string(lose_amount) + " gold!";
    EndBattle(QString::fromStdString(message));
}
