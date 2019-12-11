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

void Underworld::DrawUnderworld(Enemy *enemy, player *player) {
    this->enemy_ = enemy;
    this->player_= player;

    //EventHandler

    //Containing box coordinates (temp)

    int cwidth = 300;
    int cheight = 275;
    int cx1 = 140;
    int cy1 = 150;
    int cx2 = cx1 + cwidth;
    int cy2 = cy1 + cheight;

    int player_sprite_size = 25;


    QImage *img = new QImage(":/images/battlebackground.jpg");
    *img = img->scaled(100,100,Qt::KeepAspectRatioByExpanding);
    QBrush bg_brush(*img);
    scene_ ->setBackgroundBrush(bg_brush);

    //DRAW AND POSITION THE PLAYER
    QPixmap sprite = QPixmap(":/images/heart.png");
    sprite = sprite.scaled(player_sprite_size, player_sprite_size,Qt::KeepAspectRatio);
    Bounds bound = {cx1, cy1 , cx2 - player_sprite_size, cy2 - player_sprite_size};


    player_->setPixmap(sprite);
    player_->setBound(bound);

    //DRAW THE BOX THE PLAYER MAY MOVE AROUND IN
    ContainingBox *b = new ContainingBox(cx1, cy1, cwidth, cheight, Qt::GlobalColor::white, "");
    scene_->addItem(b);
    connect(this, &Underworld::OnBulletFired, this, &Underworld::FireBullet);

    //DRAW THE ENEMY
    enemy_->setPos(150, -170);
    scene_->addItem(enemy_);

    //Player 1 Health Bar
    HealthBar *ph = new HealthBar(cx1, cy2 + 10, cwidth, 20, player_->getMaxHealth(), player_->getHealth());
    scene_->addItem(ph);
    connect(player_, &player::HealthChanged, ph, &HealthBar::ChangeHealth);
    connect(player_, &player::PlayerDied, this, &Underworld::OnPlayerDeath);
    //Health Bar Temporary text

    //Enemy health bar
    HealthBar *eh = new HealthBar(100, -300, 400, 50, enemy_->getMaxHealth(), enemy_->getHealth());
    scene_->addItem(eh);
    connect(this, &Underworld::OnEnemyHit, eh, &HealthBar::ChangeHealth);


    //Draw boxes for options
    fight_box_ = new ContainingBox(cx1, cy2 + 50, 150, 50, Qt::GlobalColor::green, "Fight [F]");
    scene_->addItem(fight_box_);


    bribe_box_ = new ContainingBox(cx1 + 150, cy2 + 50, 150, 50, Qt::GlobalColor::green, "Bribe [B]");
    scene_->addItem(bribe_box_);

    player_->getInventory()->setPos(-20, 150);
    scene_->addItem(player_->getInventory());

    if (dynamic_cast<ComputerPlayer*>(player_)) {
        QTimer::singleShot(1000, [=](){
             MakeAIChoice();
        });
    }
}

void Underworld::MakeAIChoice() {
    int choice = rand() % 10;
    if (choice == 1) {
        Bribe();
    } else {
        OnFightClicked();
    }
}

//Function:
void Underworld::ProcessAttackPattern(std::vector<AttackPattern> s) {
    for (size_t i = 0; i < s.size(); i ++) {
        QTimer::singleShot(s[i].delay, [=](){
            if (!fight_over_) {
                FireBullet(s[i].x, s[i].y, s[i].dir);
            }
        });
    }
}

void Underworld::FireBullet(int x, int y, Direction d) {
        Bounds bound = {90, 90, 410, 410};
        Bullet *b = new Bullet(x, y, d, scene_, bound);
        scene_->addItem(b);
}

void Underworld::OnFightClicked() {
    //Send damage to the enemy
    emit OnEnemyHit(-1 * player_->getDamage());
    enemy_->changeHealth(-1 * player_->getDamage());
    scene_->update();

    if (enemy_->isDead()) {
        EnemyDeath();
        return;
    }

    InitiateFightSequence();
}

void Underworld::OnItemUsed() {
    if (enemy_->isDead()) {
        EnemyDeath();
        return;
    }
    scene_->update();
    InitiateFightSequence();
}

void Underworld::InitiateFightSequence() {
    //If the enemy is dead, don't initiate a fight sequence
    scene_->removeItem(fight_box_);
    scene_->removeItem(bribe_box_);
    fighting_ = true;

    //Add the player to the scene, do health calculations
    player_->setPos(220, 250);
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
            if (dynamic_cast<ComputerPlayer*>(player_)) {
                QTimer::singleShot(2000, [=] () {
                    MakeAIChoice();
                });
            }
        }
    });
}


void Underworld::SwitchToOverWorld() {
    scene_->clear();
    GameView &game =  GameView::GetInstance();
    Mode mode = game.get_game_mode();
    if (mode == SinglePlayer) {
        game.CreateSinglePlayerOverWorld();
    } else if (mode == TwoPlayer) {
        game.CreateTwoPlayerOverWorld();
    } else if (mode == Simulation) {
        game.CreateAIOverworld();
    }
    //If you delete the underwold object some memory is gonna leak
    delete this;
}

void Underworld::EndBattle(QString s) {
    scene_->removeItem(player_->getInventory());
    scene_->clear();
    scene_->update();

    ContainingBox *end = new ContainingBox(50, 200, 600, 200, Qt::GlobalColor::white, "");
    QGraphicsTextItem *text = new QGraphicsTextItem(s);
    text->setDefaultTextColor(Qt::GlobalColor::white);
    text->setPos(55, 210);
    //Switches back to overworld in 5 seconds
    QTimer::singleShot(3000, [=]() {
        SwitchToOverWorld();
    });
    scene_->addItem(text);
    scene_->addItem(end);

}

void Underworld::Bribe() {
    player_->changeGold(-10);
    EndBattle("You ran like a coward and lost 10 gold!");

}

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
