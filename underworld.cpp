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

//TODO constructor needs to be able to instantiate enemy
Underworld::Underworld(QGraphicsScene * main_scene)
{
    //Containing box coordinates (temp)
    int cwidth = 300;
    int cheight = 275;
    int cx1 = 140;
    int cy1 = 150;
    int cx2 = cx1 + cwidth;
    int cy2 = cy1 + cheight;

    int player_sprite_size = 25;

    this->scene = main_scene;
    QImage *img = new QImage(":/images/battlebackground.jpg");
    *img = img->scaled(100,100,Qt::KeepAspectRatioByExpanding);
    QBrush bg_brush(*img);
    scene ->setBackgroundBrush(bg_brush);

    qDebug() << scene->width();
    qDebug() << scene->height();

    //DRAW AND POSITION THE PLAYER
    QPixmap sprite = QPixmap(":/images/heart.png");
    sprite = sprite.scaled(player_sprite_size, player_sprite_size,Qt::KeepAspectRatio);
    Bounds bound = {cx1, cy1 , cx2 - player_sprite_size, cy2 - player_sprite_size};
    player *heart = new player(sprite, 5, 10, bound);
    heart->setFlag(QGraphicsItem::ItemIsFocusable,true);
    heart->setPos(200, 300);
    scene->addItem(heart);
    heart->setFocus();

    //DRAW THE BOX THE PLAYER MAY MOVE AROUND IN
    ContainingBox *b = new ContainingBox(cx1, cy1, cwidth, cheight, Qt::GlobalColor::white);
    scene->addItem(b);
    connect(this, &Underworld::OnBulletFired, this, &Underworld::FireBullet);

    //DRAW THE ENEMY
    QPixmap enemy_sprite = QPixmap(":/images/Gr8.png");
    enemy_sprite = enemy_sprite.scaled(300, 300, Qt::KeepAspectRatio);
    Enemy *e = new Enemy(enemy_sprite, 5, 10, bound);
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
    HealthBar *eh = new HealthBar(100, -300, 400, 50, 3);
    scene->addItem(eh);
    connect(this, &Underworld::OnEnemyHit, eh, &HealthBar::ChangeHealth);


    //Draw boxes for options
    ContainingBox *fight = new ContainingBox(cx1 - 50, cy2 + 50, 100, 50, Qt::GlobalColor::green);
    scene->addItem(fight);
    connect(fight, &ContainingBox::onBoxClicked, this, &Underworld::onFightClicked);

    QGraphicsTextItem *fight_text = new QGraphicsTextItem("FIGHT");
    fight_text->setDefaultTextColor(Qt::GlobalColor::green);
    fight_text->setPos(cx1 - 35, cy2 + 75);
    scene->addItem(fight_text);
}

//Function:
void Underworld::ProcessAttackPattern(std::vector<AttackPattern> s) {
    for (size_t i = 0; i < s.size(); i ++) {
        QTimer::singleShot(s[i].delay, [=](){
            FireBullet(s[i].x, s[i].y);
        });
    }
}

void Underworld::FireBullet(int x, int y) {
        Bounds bound = {100, 100, 600, 400};
        Bullet *b = new Bullet(x, y, Direction::S, scene, bound);
        scene->addItem(b);
}

void Underworld::onFightClicked() {
    //TODO ZL Set Focus to player
    std::vector<AttackPattern> a;

    int current_delay = 200;
    for (int i = 0; i < 50; i ++) {
        current_delay += 100;
        AttackPattern p = {current_delay, 80 + i * 5, 200, Direction::S};
        a.push_back(p);
    }

    //TODO change this to the amount of damage the player has
    emit OnEnemyHit(-1);

    QTimer::singleShot(1000, [=]() {
        ProcessAttackPattern(a);
    });

}
