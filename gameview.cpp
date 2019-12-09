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
GameView::GameView()
{
    //add scene
    scene = new QGraphicsScene(this);

    //add background
    scene->setSceneRect(0, 0, width(), height());

    //initialize player
    QPixmap sprite = QPixmap(":/images/player.png");
    sprite = sprite.scaled(100,100,Qt::KeepAspectRatio);
    Bounds bound = {-20000, -20000, 20000, 20000};
    player *boy = new player(sprite, 20, 10, bound, 0);
    player_ = boy;
    player_->setFlag(QGraphicsItem::ItemIsFocusable,true);


    CreateOverworld();

    connect(timer_, SIGNAL(timeout()), this, SLOT(SwitchToUnderWorld()));
    //timer_->start(2000);


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
    //add player  
    Bounds bound = {-20000, -20000, 20000, 20000};
    QPixmap sprite = QPixmap(":/images/player.png");
    sprite = sprite.scaled(100,100,Qt::KeepAspectRatio);
    player_->setBound(bound);
    player_->setPixmap(sprite);

    for(int i = 0; i < 50; i++)
    {
        Toilet *tmp = new Toilet();
        tmp->setPos(rand()%-2000, rand()%2000);
        scene->addItem(tmp);
    }

    scene->addItem(player_);
    scene->addItem(player_->inventory_);
    player_->setFocus();
}

void GameView::SwitchToUnderWorld() {
    timer_->stop();

    Enemy * e = MonsterFactory::GetEnemy(EnemyType::DweebFish);
    Underworld * u = new Underworld(scene);

    //PLAYER MUST BE REMOVED FROM SCENE BEFORE CLEARED OR IT WILL BE DELETED.
    scene->removeItem(player_);
    scene->removeItem(player_->inventory_);
    scene->clear();
    u->DrawUnderworld(e, player_);

    connect(this, &GameView::onKeyPressed, u, &Underworld::onKeyPress);
}

void GameView::keyPressEvent(QKeyEvent * event) {
    emit onKeyPressed(event);
    QGraphicsView::keyPressEvent(event);
}
