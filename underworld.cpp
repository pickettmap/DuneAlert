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
    scene = main_scene;
}

void Underworld::DrawUnderworld(Enemy *e, player *p) {
    //EventHandler

    //Containing box coordinates (temp)
    this->e = e;

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
    scene ->setBackgroundBrush(bg_brush);

    //DRAW AND POSITION THE PLAYER
    QPixmap sprite = QPixmap(":/images/heart.png");
    sprite = sprite.scaled(player_sprite_size, player_sprite_size,Qt::KeepAspectRatio);
    Bounds bound = {cx1, cy1 , cx2 - player_sprite_size, cy2 - player_sprite_size};
    player *heart = new player(sprite, p->health_, p->damage_, bound);
    heart->setFlag(QGraphicsItem::ItemIsFocusable,true);
    heart->setPos(200, 300);
    scene->addItem(heart);
    heart->setFocus();
    this->p = heart;

    //DRAW THE BOX THE PLAYER MAY MOVE AROUND IN
    ContainingBox *b = new ContainingBox(cx1, cy1, cwidth, cheight, Qt::GlobalColor::white, "");
    scene->addItem(b);
    connect(this, &Underworld::OnBulletFired, this, &Underworld::FireBullet);

    //DRAW THE ENEMY
    e->setPos(150, -170);
    scene->addItem(e);

    //Player 1 Health Bar
    HealthBar *ph = new HealthBar(cx1 - 40, cy2 + 10, 200 , 20, 5);
    scene->addItem(ph);

    //Health Bar Temporary text
    QGraphicsTextItem *text = new QGraphicsTextItem("20/20");
    text->setDefaultTextColor(Qt::GlobalColor::white);
    text->setPos(cx1 - 30, cy2 + 10);
    scene->addItem(text);

    //Enemy health bar
    HealthBar *eh = new HealthBar(100, -300, 400, 50, e->health_);
    scene->addItem(eh);
    connect(this, &Underworld::OnEnemyHit, eh, &HealthBar::ChangeHealth);


    //Draw boxes for options
    ContainingBox *fight = new ContainingBox(cx1 - 50, cy2 + 50, 100, 50, Qt::GlobalColor::green, "Fight");
    scene->addItem(fight);
    connect(fight, &ContainingBox::onBoxClicked, this, &Underworld::onFightClicked);

    ContainingBox *item = new ContainingBox(cx1 + 100, cy2 + 50, 100, 50, Qt::GlobalColor::green, "Bribe");
    scene->addItem(item);
//    connect(fight, &ContainingBox::onBoxClicked, this, &Underworld::onFightClicked);


    /*  ITEMS
     * 1) Each player has an inventory attached to it
     * 2) Inventory will be displayed to the side with corresponding keystrokes.
     * 3) Player can hit a keystroke and the item will be used
     *
     * 4) Inventory Updates
     *
     */
    Inventory * inv = new Inventory(-20, 150);
    scene->addItem(inv);
}

//Function:
void Underworld::ProcessAttackPattern(std::vector<AttackPattern> s) {
    for (size_t i = 0; i < s.size(); i ++) {
        QTimer::singleShot(s[i].delay, [=](){
            FireBullet(s[i].x, s[i].y, s[i].dir);
        });
    }
}

void Underworld::FireBullet(int x, int y, Direction d) {
        Bounds bound = {100, 100, 600, 400};
        Bullet *b = new Bullet(x, y, d, scene, bound);
        scene->addItem(b);
}

void Underworld::onFightClicked() {

    //TODO change this to the amount of damage the player has

    emit OnEnemyHit(-1);
    e->changeHealth(-1);

    if (e->isDead()) {
        EndBattle();
        return;
    }

    QTimer::singleShot(1000, [=]() {
        ProcessAttackPattern(e->GetFightPattern());
    });

}


void Underworld::SwitchToOverWorld() {
    scene->clear();
    //todo add code to switch back to overworld.
}

void Underworld::EndBattle() {
    scene->clear();

    ContainingBox *end = new ContainingBox(50, 200, 600, 200, Qt::GlobalColor::white, "");

    QGraphicsTextItem *text = new QGraphicsTextItem("You Defeated Lesser Dog and Got Stuff!");
    text->setDefaultTextColor(Qt::GlobalColor::white);
    text->setPos(55, 210);
    //Switches back to overworld in 5 seconds
    QTimer::singleShot(5000, [=]() {
        SwitchToOverWorld();
    });
    scene->addItem(text);
    scene->addItem(end);

}

void Underworld::onKeyPress(QKeyEvent *event) {
    qDebug() << event->key();
}
