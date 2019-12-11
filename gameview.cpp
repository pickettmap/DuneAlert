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
#include "computerplayer.h"
#include "startmenu.h"

GameView::GameView()
{
    //add scene
    scene = new QGraphicsScene(this);

    resize(1800,1200);
    //add background
    scene->clear();
    QImage *img = new QImage(":/images/grass.png");
    *img = img->scaled(100,100,Qt::KeepAspectRatioByExpanding);
    QBrush bg_brush(*img);
    scene ->setBackgroundBrush(bg_brush);
    scene->setSceneRect(0, 0, width(), height());

    setScene(scene);
    setSceneRect(scene->sceneRect());
    setMinimumSize(width(), height());

    QAbstractScrollArea::setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    QAbstractScrollArea::setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    timer1->setInterval(100);
    connect(timer1, SIGNAL(timeout()), this, SLOT(CheckGame()));
}

void GameView::CreateBackGround() {
    in_overworld_ = true;
    switching_to_overworld_ = true;
    QTimer::singleShot(1000, [=](){
        switching_to_overworld_ = false;
    });
    if(mode_!=Mode::Simulation)
    {
        timer1->start();
    }
    scene->clear();
    QImage *img = new QImage(":/images/grass.png");
    *img = img->scaled(100,100,Qt::KeepAspectRatioByExpanding);
    QBrush bg_brush(*img);
    scene ->setBackgroundBrush(bg_brush);
}
void GameView::CreateSinglePlayerOverWorld()
{
    CreateBackGround();
    QPixmap sprite = QPixmap(":/images/player.png");
    sprite = sprite.scaled(100,100,Qt::KeepAspectRatio);
    Bounds bound = {0, 0, width(), height()};

    //Add one player and make toilets
    if (!player_) {
        player *boy = new player(sprite, 20, 1, bound, 0);
        player_ = boy;
        //Default position
        player_->setPos(100, 100);
        scene->addItem(player_);

        int arr[2] = {100,100};
        makeToilets(arr);
    }
    else {
        scene->addItem(player_);
        player_->setPos(player_one_position_[0], player_one_position_[1]);
        makeToilets(player_one_position_);
    }

    player_->setBound(bound);
    player_->setPixmap(sprite);
    player_->getInventory()->setPos(200, 400);
    scene->addItem(player_->getInventory());
    connect(this, &GameView::onPOneKeyPressed, player_, &player::onKeyPressed);
    connect(this, &GameView::onKeyRelease, player_, &player::onKeyRelease);

    //Draw Score Display
    StatsDisplay * d = player_->getStats();
    scene->addItem(d);
    d->setPos(200,200);
    connect(player_, &player::StatsUpdated, d, &StatsDisplay::StatsUpdated);

}

void GameView::makeToilets(int arr[2])
{
    for(int i = 0; i < 50; i++)
    {
        int randx = rand()%width();
        int randy = rand()%height();

        if(randx > (arr[0] + 50) || randx < (arr[0] - 50))
        {
            if((randy > (arr[1]) + 50) || randy < (arr[1] - 50))
            {
                Toilet *tmp = new Toilet();
                tmp->setPos(randx,randy);
                scene->addItem(tmp);
            }
        }
    }
}

void GameView::CreateTwoPlayerOverWorld() {
    CreateSinglePlayerOverWorld();

    Bounds bound2 = {0, 0, width(), height()};
    QPixmap sprite2 = QPixmap(":/images/sans_undertale.png");
    sprite2 = sprite2.scaled(100,100,Qt::KeepAspectRatio);

    if (!player2_) {
        SecondPlayer *boy2 = new SecondPlayer(sprite2, 20, 1, bound2, 0);
        player2_ = boy2;
        player2_->setPos(400, 400);
    }

    else if (player2_) {
        player2_->setPos(player_two_position_[0], player_two_position_[1]);
    }

    player2_->setPixmap(sprite2);
    player2_->setBound(bound2);
    player2_->getInventory()->setPos(width()-500, 200);

    scene->addItem(player2_);
    scene->addItem(player2_->getInventory());

    connect(this, &GameView::onPTwoKeyPressed, player2_, &SecondPlayer::onKeyPressed);
    connect(this, &GameView::onKeyRelease, player2_, &SecondPlayer::onKeyRelease);

    //Change to be second player stats ty
    StatsDisplay * d = player2_->getStats();
    scene->addItem(d);
    connect(player2_, &player::StatsUpdated, d, &StatsDisplay::StatsUpdated);
}

void GameView::CreateAIOverworld()
{
    CreateBackGround();
    Bounds bounds = {0, 0, width(), height()};
    QPixmap sprite = QPixmap(":/images/player.png");
    sprite = sprite.scaled(100,100,Qt::KeepAspectRatio);
    ComputerPlayer * p = new ComputerPlayer(sprite, 20, 5, bounds, 0);

    if (!ai) {
        ComputerPlayer *art = new ComputerPlayer(sprite, 20, 1, bounds, 0);
        ai = art;
        ai->setPos(400, 400);
        ai_position_[0] = 400;
        ai_position_[1] = 400;
    }

    else if (ai) {
        ai->setPos(ai_position_[0], ai_position_[1]);
    }
    ai->setPixmap(sprite);
    ai->setBound(bounds);

    scene->addItem(ai);
    makeToilets(ai_position_);

}


void GameView::RemovePlayer() {
    if (player_) {
        scene->removeItem(player_);
        scene->removeItem(player_->getInventory());
        scene->removeItem(player_->getStats());
    }
    if (player2_) {
        scene->removeItem(player2_);
        scene->removeItem(player2_->getInventory());
        scene->removeItem(player2_->getStats());
    }

    if (ai) {
        scene->removeItem(ai);
    }
}

void GameView::SwitchToUnderWorld(player *p, Enemy *e) {
    if (player_) {
        player_one_position_[0]=player_->x();
        player_one_position_[1]=player_->y();
    }

    if (player2_) {
        player_two_position_[0]=player2_->x();
        player_two_position_[1]=player2_->y();
    }

    if (ai) {
        ai_position_[0] = ai->x();
        ai_position_[1] = ai->y();
        determineAIFightSequence();
        return;
    }

    switching_to_underworld_ = true;
    QTimer::singleShot(1000, [=](){
        switching_to_underworld_ = false;
    });
    in_overworld_ = false;
    Underworld * u = new Underworld(scene);
    RemovePlayer();
    scene->clear();
    u->DrawUnderworld(e, p);

    connect(this, &GameView::onKeyPressed, u, &Underworld::OnKeyPress);
}


void GameView::keyPressEvent(QKeyEvent * event) {
    if (switching_to_underworld_) {
        return;
    }
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

void GameView::determineAIFightSequence() {
    int outcome = rand() % 3;
    if (outcome == 2) {
        ai->changeGold(10);
    }
    else if (outcome == 1) {
        ai->changeGold(-10);
    }
    else if (outcome == 1) {
        ai->changeGold(-20);
    }
    scene->update();
}

void GameView::EndGame() {
    StartMenu m;
    m.setMinimumSize(800,800);
    m.show();
    RemovePlayer();
    switching_to_overworld_ = true;
    scene->clear();
    Inventory * n = ai ->getInventory();
    emit onAIComplete(ai->getGold());
    n = nullptr;
    ai = nullptr;
    close();
}

void GameView::GameOver()
{
    timer1->stop();
    scene->clear();
    std::string text;
    if(mode_==Mode::TwoPlayer)
    {
        text = "Player one finished with " + std::to_string(player_->getGold()) + " gold!";
        text += "\n Player two finished with "+ std::to_string(player_->getGold()) + " gold!";
    }
    else if(mode_==Mode::SinglePlayer)
    {
        if(win)
        {
            if(mode_==Mode::SinglePlayer)
            {
                text = "Congratulations!";
                text += "\n You won with " + std::to_string(player_->getGold()) + " gold!";
            }
        }
        else
        {
            text = "Geeeeeeeet Dunked On!!!!";
        }
    }
    ContainingBox *box = new ContainingBox(0,0, width(),height(),Qt::GlobalColor::white,text);
    scene->addItem(box);

}

void GameView::CheckGame()
{
    if(mode_==Mode::TwoPlayer)
    {
        int p1gold = player_->getGold();
        int p2gold = player2_->getGold();

        if(p1gold >= 50 || p2gold >= 50)
        {
            GameOver();
        }

        else if(p1gold <= -20 || p2gold <= -20)
        {
            GameOver();
        }
    }
    else if(mode_==Mode::SinglePlayer)
    {
        if(player_->getGold()>=50)
        {
            win = true;
            GameOver();
        }
        else if(player_->getGold()<=-20)
        {
            win = false;
            GameOver();
        }
    }
}
