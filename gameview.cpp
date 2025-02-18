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
#include "monsterfactory.h"
#include "secondplayer.h"
#include "statsdisplay.h"
#include "computerplayer.h"
#include "startmenu.h"
#include "scenery.h"
#include "item.h"
/*
Function: GameView constructor
Params: None
Desc: Initializes scene and sets background tiles
Returns: GameView
*/
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

    timer1->setInterval(1000);
    connect(timer1, SIGNAL(timeout()), this, SLOT(CheckGame()));
}

/*
Function: CreateBackground
Params: None
Desc: Used when switching between overworld and underworld
Initializes overworld grass background
Returns: None
*/
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

/*
Function: CreateSinglePlayerOverWorld
Params: None
Desc: Initializses player character, scenery objects and
player inventory/stats display
Returns: None
*/
void GameView::CreateSinglePlayerOverWorld()
{

    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/overworld.mp3"));
    music->play();
    CreateBackGround();
    QPixmap sprite = QPixmap(":/images/player.png");
    sprite = sprite.scaled(100,100,Qt::KeepAspectRatio);
    Bounds bound = {0, 0, width(), height()};

    //Add one player and make toilets
    if (!player_) {
        Player *boy = new Player(sprite, 20, 1, bound, 0, Qt::GlobalColor::blue);
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
    connect(this, &GameView::onPOneKeyPressed, player_, &Player::onKeyPressed);
    connect(this, &GameView::onKeyRelease, player_, &Player::onKeyRelease);

    //Draw Score Display
    StatsDisplay * d = player_->getStats();
    scene->addItem(d);

    connect(player_, &Player::StatsUpdated, d, &StatsDisplay::StatsUpdated);
    d->setPos(0,0);


}

/*
Function: MakeToilets
Params: int arr[2] which holds player's x/y coordinates
Desc: Places toilets in overworld everywhere except where player is
Returns: None
*/
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
                int rand_env = rand() % 3;
                if (rand_env == 0){
                    Toilet *tmp = new Toilet();
                    tmp->setPos(randx,randy);
                    scene->addItem(tmp);
                }
                else if (rand_env == 1) {
                    Chest *tmp = new Chest();
                    tmp->setPos(randx, randy);
                    scene->addItem(tmp);

                }
               else {
                    Crate *tmp = new Crate();
                    tmp->setPos(randx, randy);
                    scene->addItem(tmp);
                }
            }
        }
    }
}

/*
Function: CreateTwoPlayerOverWorld
Params: None
Desc: Utilizes singleplayeroverworld construction but also
adds a second player along with second player's inventory/stats
Returns: None
*/
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
    player2_->getInventory()->setPos(width()-250, 400);

    scene->addItem(player2_);
    scene->addItem(player2_->getInventory());

    connect(this, &GameView::onPTwoKeyPressed, player2_, &SecondPlayer::onKeyPressed);
    connect(this, &GameView::onKeyRelease, player2_, &SecondPlayer::onKeyRelease);

    //Change to be second player stats ty
    StatsDisplay * d = player2_->getStats();
    scene->addItem(d);

    d->setPos(width()-450,0);
    connect(player2_, &Player::StatsUpdated, d, &StatsDisplay::StatsUpdated);

}

/*
Function: CreateAIOverworld
Params: None
Desc: Creates OverWorld for simulated game, creates ComputerPlayer object
Returns:
*/
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

/*
Function: RemovePlayer
Params: None
Desc: Removes Player and their inventory/stats from overworld
Prevents memory issues when clearing overworld
Returns: None
*/
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

/*
Function: SwitchToUnderWorld
Params: Player *p, Enemy *e
Desc: Stores player's overworld position so it can be reloaded
Clears overworld scene
Draws underworld scene with player and enemy
Returns: None
*/
void GameView::SwitchToUnderWorld(Player *p, Enemy *e) {
    music->stop();
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

/*
Function: keyPressEvent
Params: QKeyEvent *event
Desc: Checks for key types to handle movement
Handles different sets of keys for first/second player movement
First player set: WASD
Second player set: Arrow Keys
On corresponding key press, key event is emited as signal
Returns: none
*/
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

/*
Function: keyReleaseEvent
Params: QKeyEvent *event
Desc: emits keyRelease event as signal
Returns: None
*/
void GameView::keyReleaseEvent(QKeyEvent * event) {
    emit onKeyRelease(event);
}

/*
Function: determineAIFightSequence
Params: None
Desc: Handles fight logic for result of battle in simulation
Randomly decides if AI wins, loses, or runs away
Returns: None
*/
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

/*
Function: EndGame
Params: None
Desc: Handles end of game for simulation
Clears screen and returns to menu
Returns: None
*/
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

/*
Function: GameOver
Params: None
Desc: Handles end of game logic for Human controlled games
Clears scene and displays results
Returns: None
*/
void GameView::GameOver()
{
    timer1->stop();
    music->setMedia(QUrl("qrc:/sounds/gameend.mp3"));
    music->play();
    scene->removeItem(player_);
    scene->removeItem(player_->getInventory());
    scene->removeItem(player_->getStats());
    if (player2_) {
        scene->removeItem(player2_);
    }
    timer1->stop();
    scene->clear();
    std::string text;
    if(mode_==Mode::TwoPlayer)
    {
        text = "Player one finished with " + std::to_string(player_->getGold()) + " gold!";
        text += "\n Player two finished with "+ std::to_string(player2_->getGold()) + " gold!";
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
            text = "You Lost! Geeeeeeeet Dunked On!!!!";
        }
    }
    ContainingBox *box = new ContainingBox(0,0, width(),height(),Qt::GlobalColor::white,text);
    scene->addItem(box);

}

/*
Function: CheckGame
Params: None
Desc: Continually checks if any player has won or lost
Calls GameOver when conditions are met
Win if player has over 50 coins
Lose if player has less than -20
Returns: None
*/
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
