#include "gameview.h"
#include "underworld.h"
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include "gun.h"
#include "toilet.h"
#include "burger.h"
#include "monsterfactory.h"
#include "tutu.h"
#include "secondplayer.h"
#include "statsdisplay.h"

GameView::GameView()
{
    //add scene
    scene = new QGraphicsScene(this);

    //add background
    scene->setSceneRect(0, 0, width(), height());
    //initialize player
    QPixmap sprite = QPixmap(":/images/player.png");
    sprite = sprite.scaled(100,100,Qt::KeepAspectRatio);

    Bounds bound = {0, 0, width(), height()};
    //Bounds bound = {-20000, -20000, 20000, 20000};
    player *boy = new player(sprite, 20, 1, bound, 0);
    player_ = boy;
    player_->setFlag(QGraphicsItem::ItemIsFocusable,true);


    CreateOverworld();

    connect(timer_, SIGNAL(timeout()), this, SLOT(SwitchToUnderWorld()));

    setScene(scene);
    setSceneRect(scene->sceneRect());
    setMinimumSize(1800, 1200);
}

void GameView::CreateOverworld()
{
    scene->clear();
    QImage *img = new QImage(":/images/grass.png");
    *img = img->scaled(100,100,Qt::KeepAspectRatioByExpanding);
    QBrush bg_brush(*img);
    scene ->setBackgroundBrush(bg_brush);

    //Items for testing to be removed
    Burger *b = new Burger();
    b->setPos(500, 500);
    scene->addItem(b);

    Tutu *t = new Tutu();
    t->setPos(200, 200);
    scene->addItem(t);



    //Bounds bound = {-20000, -20000, 20000, 20000};
    Bounds bound = {0, 0, width(), height()};
    QPixmap sprite = QPixmap(":/images/player.png");
    sprite = sprite.scaled(100,100,Qt::KeepAspectRatio);
    player_->setBound(bound);
    player_->setPixmap(sprite);
    player_->getInventory()->setPos(-200, -200);

    for(int i = 0; i < 50; i++)
    {
        Toilet *tmp = new Toilet();
        tmp->setPos(rand()%-2000, rand()%2000);
        scene->addItem(tmp);
    }


    scene->addItem(player_);
    scene->addItem(player_->getInventory());

    player_->setFocus();

//    QTimer::singleShot(5000, [=]() {
//        SwitchToUnderWorld();
//    });
    connect(this, &GameView::onPOneKeyPressed, player_, &player::onKeyPressed);
    connect(this, &GameView::onKeyRelease, player_, &player::onKeyRelease);
    //Testing for Stats display
    StatsDisplay * d = new StatsDisplay(200, 200, "Player 1", player_->getMaxHealth(), player_->getHealth(), player_->getGold(), player_->getDamage(), Qt::GlobalColor::blue);
    scene->addItem(d);
    connect(player_, &player::StatsUpdated, d, &StatsDisplay::StatsUpdated);
    //TODO Let the user have a choice on 2p or 1p
    //Testing for 2p
    QPixmap sprite2 = QPixmap(":/images/player.png");
    sprite2 = sprite2.scaled(100,100,Qt::KeepAspectRatio);
    Bounds bound2 = {-20000, -20000, 20000, 20000};
    SecondPlayer *boy2 = new SecondPlayer(sprite2, 20, 1, bound2, 0);
    boy2->setPos(100, 100);
    scene->addItem(boy2);
    scene->addItem(boy2->getInventory());
    connect(this, &GameView::onPTwoKeyPressed, boy2, &SecondPlayer::onKeyPressed);
    connect(this, &GameView::onKeyRelease, boy2, &SecondPlayer::onKeyRelease);
}

void GameView::SwitchToUnderWorld() {
    timer_->stop();

    Enemy * e = MonsterFactory::GetEnemy(EnemyType::DweebFish);
    Underworld * u = new Underworld(scene);

    //PLAYER MUST BE REMOVED FROM SCENE BEFORE CLEARED OR IT WILL BE DELETED.
    scene->removeItem(player_);
    scene->removeItem(player_->getInventory());
    //Second player needs to be removed here too
    scene->clear();
    u->DrawUnderworld(e, player_);

    connect(this, &GameView::onKeyPressed, u, &Underworld::OnKeyPress);

}

void GameView::keyPressEvent(QKeyEvent * event) {

    std::vector<int> first_person_keys = { Qt::Key_W, Qt::Key_S, Qt::Key_D, Qt::Key_A, Qt::Key_Escape };
    std::vector<int> second_person_keys = { Qt::Key_Up, Qt::Key_Down, Qt::Key_Left, Qt::Key_Right, Qt::Key_Control};

    //Emit event if it is wasd
    if (std::find(first_person_keys.begin(), first_person_keys.end(), event->key()) != first_person_keys.end()) {
        emit onPOneKeyPressed(event);
    }
    //Emit event if arrow keys
    else if (std::find(second_person_keys.begin(), second_person_keys.end(), event->key()) != second_person_keys.end()) {
        emit onPTwoKeyPressed(event);
    }
    //Emit other events to underworld.
    emit onKeyPressed(event);

}

void GameView::keyReleaseEvent(QKeyEvent * event) {
    emit onKeyRelease(event);
}
