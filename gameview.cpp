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
    scene->clear();
    QImage *img = new QImage(":/images/grass.png");
    *img = img->scaled(100,100,Qt::KeepAspectRatioByExpanding);
    QBrush bg_brush(*img);
    scene ->setBackgroundBrush(bg_brush);

    scene->setSceneRect(0, 0, width(), height());
    //initialize player

//    CreateOverworld();

    connect(timer_, SIGNAL(timeout()), this, SLOT(SwitchToUnderWorld()));

    setScene(scene);
    setSceneRect(scene->sceneRect());
    setMinimumSize(1800, 1200);
}

void GameView::CreateSinglePlayerOverWorld()
{
    scene->clear();
    QImage *img = new QImage(":/images/grass.png");
    *img = img->scaled(100,100,Qt::KeepAspectRatioByExpanding);
    QBrush bg_brush(*img);
    scene ->setBackgroundBrush(bg_brush);

    QPixmap sprite = QPixmap(":/images/player.png");
    sprite = sprite.scaled(100,100,Qt::KeepAspectRatio);
    Bounds bound = {0, 0, width(), height()};

    //Add one player
    if (!player_) {
        player *boy = new player(sprite, 20, 1, bound, 0);
        player_ = boy;
    }

    player_->setBound(bound);
    player_->setPixmap(sprite);
    player_->getInventory()->setPos(-200, -200);
    scene->addItem(player_);
    scene->addItem(player_->getInventory());
    connect(this, &GameView::onPOneKeyPressed, player_, &player::onKeyPressed);
    connect(this, &GameView::onKeyRelease, player_, &player::onKeyRelease);

    //Draw Score Display
    StatsDisplay * d = new StatsDisplay(200, 200, "Player 1", player_->getMaxHealth(), player_->getHealth(), player_->getGold(), player_->getDamage(), Qt::GlobalColor::blue);
    scene->addItem(d);
    connect(player_, &player::StatsUpdated, d, &StatsDisplay::StatsUpdated);


    //Items for testing to be removed
    Burger *b = new Burger();
    b->setPos(500, 500);
    scene->addItem(b);

    Tutu *t = new Tutu();
    t->setPos(200, 200);
    scene->addItem(t);

    for(int i = 0; i < 50; i++)
    {
        Toilet *tmp = new Toilet();
        tmp->setPos(600,rand()%2000);
        scene->addItem(tmp);
    }


}

void GameView::CreateTwoPlayerOverWorld() {
    CreateSinglePlayerOverWorld();

    Bounds bound2 = {-20000, -20000, 20000, 20000};
    QPixmap sprite2 = QPixmap(":/images/player.png");
    sprite2 = sprite2.scaled(100,100,Qt::KeepAspectRatio);

    if (!player2_) {
        SecondPlayer *boy2 = new SecondPlayer(sprite2, 20, 1, bound2, 0);
        player2_ = boy2;
    }

    player2_->setPixmap(sprite2);
    player2_->setBound(bound2);
    player2_->setPos(100, 100);
    player2_->getInventory()->setPos(500, 500);

    scene->addItem(player2_);
    scene->addItem(player2_->getInventory());

    connect(this, &GameView::onPTwoKeyPressed, player2_, &SecondPlayer::onKeyPressed);
    connect(this, &GameView::onKeyRelease, player2_, &SecondPlayer::onKeyRelease);

    //Change to be second player stats ty
    StatsDisplay * d = new StatsDisplay(200, 200, "Player 1", player_->getMaxHealth(), player_->getHealth(), player_->getGold(), player_->getDamage(), Qt::GlobalColor::blue);
    scene->addItem(d);
    connect(player_, &player::StatsUpdated, d, &StatsDisplay::StatsUpdated);
}

void GameView::SwitchToUnderWorld(player *p, Enemy *e) {
    Underworld * u = new Underworld(scene);
    //Remove player and inventory from scene so memory doesn't break
    if (player_) {
        scene->removeItem(player_);
        scene->removeItem(player_->getInventory());
    }
    if (player2_) {
        scene->removeItem(player2_);
        scene->removeItem(player2_->getInventory());
    }

    scene->clear();
    u->DrawUnderworld(e, p);

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
