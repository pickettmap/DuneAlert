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
    this->e_ = enemy;
    this->p_= player;

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


    p_->setPixmap(sprite);
    p_->setPos(200, 300);
    p_->setBound(bound);

    //DRAW THE BOX THE PLAYER MAY MOVE AROUND IN
    ContainingBox *b = new ContainingBox(cx1, cy1, cwidth, cheight, Qt::GlobalColor::white, "");
    scene_->addItem(b);
    connect(this, &Underworld::OnBulletFired, this, &Underworld::FireBullet);

    //DRAW THE ENEMY
    e_->setPos(150, -170);
    scene_->addItem(e_);

    //Player 1 Health Bar
    HealthBar *ph = new HealthBar(cx1 - 40, cy2 + 10, 200, 20, p_->health_);
    scene_->addItem(ph);
    connect(p_, &player::HealthChanged, ph, &HealthBar::ChangeHealth);
    connect(p_, &player::PlayerDied, this, &Underworld::onPlayerDeath);
    //Health Bar Temporary text

    //Enemy health bar
    HealthBar *eh = new HealthBar(100, -300, 400, 50, e_->health_);
    scene_->addItem(eh);
    connect(this, &Underworld::OnEnemyHit, eh, &HealthBar::ChangeHealth);


    //Draw boxes for options
    fight_box_ = new ContainingBox(cx1, cy2 + 50, 150, 50, Qt::GlobalColor::green, "Fight [F]");
    scene_->addItem(fight_box_);


    bribe_box_ = new ContainingBox(cx1 + 150, cy2 + 50, 150, 50, Qt::GlobalColor::green, "Bribe [B]");
    scene_->addItem(bribe_box_);

    p_->inventory_->setPos(-20, 150);
    scene_->addItem(p_->getInventory());
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

void Underworld::onFightClicked() {
    //Send damage to the enemy
    emit OnEnemyHit(-1 * p_->getDamage());
    e_->changeHealth(-1 * p_->getDamage());
    scene_->update();

    if (e_->isDead()) {
        EnemyDeath();
        return;
    }

    InitiateFightSequence();
}

void Underworld::onItemUsed() {
    if (e_->isDead()) {
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
    scene_->addItem(p_);
    p_->setFocus();



    //After a 1 second delay, initiate the bullets
    QTimer::singleShot(1000, [=]() {
        ProcessAttackPattern(e_->GetFightPattern());
    });

    //After all bullets have been fired plus a few seconds, remove the player from the battle.
    QTimer::singleShot(e_->getFightDuration() + 2500, [=] () {
        if(!fight_over_) {
            scene_->addItem(fight_box_);
            scene_->addItem(bribe_box_);
            scene_->removeItem(p_);
            fighting_ = false;
        }
    });
}


void Underworld::SwitchToOverWorld() {
    scene_->clear();
    GameView &game =  GameView::GetInstance();
    game.CreateOverworld();
    //If you delete the underwold object some memory is gonna leak
    delete this;
}

void Underworld::EndBattle(QString s) {
    scene_->removeItem(p_);
    scene_->removeItem(p_->inventory_);
    scene_->clear();
    scene_->update();

    ContainingBox *end = new ContainingBox(50, 200, 600, 200, Qt::GlobalColor::white, "");
    QGraphicsTextItem *text = new QGraphicsTextItem(s);
    text->setDefaultTextColor(Qt::GlobalColor::white);
    text->setPos(55, 210);
    //Switches back to overworld in 5 seconds
    QTimer::singleShot(5000, [=]() {
        SwitchToOverWorld();
    });
    scene_->addItem(text);
    scene_->addItem(end);

}

void Underworld::Bribe() {
    p_->changeGold(-10);
    EndBattle("You ran like a coward and lost 10 gold!");

}

void Underworld::EnemyDeath() {
    fight_over_ = true;
    p_->changeGold(e_->getGold());
    std::string message = "You killed " + e_->getName() + " and received " + std::to_string(e_->getGold()) + " gold. ";

    if (e_->getItem()){
        p_->getInventory()->AddItem(e_->getItem());
        message += "They were also carrying a " + e_->getItem()->getName() + "!";
    }

    QString q = QString::fromStdString(message);


    EndBattle(q);
}

void Underworld::onKeyPress(QKeyEvent *event) {
    //Remove this line for quick underworld testing
    if (fighting_)
        return;
    if (event->key() == Qt::Key::Key_F) {
        onFightClicked();
    }
    if (event->key() == Qt::Key::Key_B) {
        Bribe();
    }
    if (event->key() == Qt::Key::Key_1) {
        p_->useItem(0);
    }
    if (event->key() == Qt::Key::Key_2) {
        p_->useItem(1);
    }
    if (event->key() == Qt::Key::Key_2) {
        p_->useItem(2);
    }
    scene_->update();
}

void Underworld::onPlayerDeath() {
    fight_over_ = true;
    int lose_amount = -20;
    if(p_->isDead()) {
        p_->changeGold(lose_amount);
    }
    std::string message = "You lost to " + e_->getName() + " and lost " + std::to_string(lose_amount) + " gold!";
    EndBattle(QString::fromStdString(message));
}
