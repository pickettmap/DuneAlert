#include "startmenu.h"
#include "gameview.h"
#include "finalgraph.h"

#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
/*
Function: StartMenu Constructor
Params: parent
Desc: Instantiates the start menu with necessary parts
Returns: none
*/
StartMenu::StartMenu(QWidget *parent)
{
    GameView& game = GameView::GetInstance();
    connect( &game, &GameView::onAIComplete, this, &StartMenu::UpdateGraph);
    QLabel *title = new QLabel("DUNEALERT",this);
    title->setAlignment(Qt::AlignHCenter);
    QLabel *title2 = new QLabel("Use WASD to move around. During fights, press F to fight and B to bribe. To use an item, during fights press the corresponding numeric button.",this);
    title2->setAlignment(Qt::AlignHCenter);

    QPushButton *play_btn = new QPushButton("One Player", this);
    QPushButton *two_play_btn = new QPushButton("Two Player", this);
    QPushButton *ai = new QPushButton("Simulation", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addWidget(title2);
    layout->addWidget(play_btn);

    layout->addWidget(two_play_btn);
    layout->addWidget(ai);

    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsView *view = new QGraphicsView();
    view->setScene(scene);
    layout->addWidget(view);

    wins_ = new FinalGraph(-50, 5, 5, Qt::GlobalColor::blue);
    loses_ = new FinalGraph(-50, 50, 5, Qt::GlobalColor::red);
    l = new QLabel("Games Played: 0");
    layout->addWidget(l);
    scene->addText("Wins    Loses");

    scene->addItem(wins_);
    scene->addItem(loses_);
    view->show();

    connect(two_play_btn, SIGNAL(clicked()), this, SLOT(PlayTwoPlayer()));
    connect(play_btn,SIGNAL(clicked()),this,SLOT(PlaySinglePlayer()));
    connect(ai,SIGNAL(clicked()),this,SLOT(PlaySimulation()));

    setLayout(layout);

}
/*
Function: play_single_player
Params: none
Desc: Calls the game view to create a new game in single player mode.
Returns: none
*/

void StartMenu::PlaySinglePlayer() {
    close();
    GameView& game = GameView::GetInstance();
    game.SetMode(Mode::SinglePlayer);
    game.CreateSinglePlayerOverWorld();
    game.show();

}
/*
Function: play_two_player
Params: none
Desc: Calls the game view to create a new game in two player mode.
Returns: none
*/
void StartMenu::PlayTwoPlayer() {
    close();
    GameView& game = GameView::GetInstance();
    game.SetMode(Mode::TwoPlayer);
    game.CreateTwoPlayerOverWorld();
    game.show();
}

/*
Function: play_simulation
Params: none
Desc: Plays one round of the simulation
Returns: none
*/
void StartMenu::PlaySimulation() {
    //Each ai encounter lasts 30 seconds
    int ai_duration = 30000;
    GameView& game = GameView::GetInstance();
    //After the ai_duration is over, the game ends and the score is tallied.
    QTimer::singleShot(ai_duration, [=](){
        GameView& game = GameView::GetInstance();
        game.EndGame();
    });
    game.SetMode(Mode::Simulation);
    game.CreateAIOverworld();
    game.show();
}

/*
Function: UpdateGraph
Params: gold, final gold value in a game
Desc: Given the final gold value of a simulated game, calculates whether or not the ai could be considered winning, then updates the graph.
Returns: none
*/
void StartMenu::UpdateGraph(int gold) {
    //If the simulated player ends with more than 0 gold count it as a win!
    if (gold >= 0) {
        win_count_ ++;
    } else {
        loss_count_ ++;
    }
    float base_height = 100;
    int total_games = win_count_ + loss_count_;
    wins_->setHeight(-(win_count_ / (loss_count_ + win_count_)) * base_height);
    loses_->setHeight(-(loss_count_ / (loss_count_ + win_count_)) * base_height);
    QString s = QString::fromStdString("Games Played: " + std::to_string(total_games));
    l->setText(s);
//    scene_->update();

}
