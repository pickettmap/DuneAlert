#include "startmenu.h"
#include "gameview.h"

#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

StartMenu::StartMenu(QWidget *parent)
{
    QLabel *title = new QLabel("DUNEALERT",this);
    title->setAlignment(Qt::AlignHCenter);
    QLabel *title2 = new QLabel("Use WASD to move around",this);
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


    connect(two_play_btn, SIGNAL(clicked()), this, SLOT(play_two_player()));
    connect(play_btn,SIGNAL(clicked()),this,SLOT(play_single_player()));
    connect(ai,SIGNAL(clicked()),this,SLOT(play_simulation()));

    setLayout(layout);

}


void StartMenu::play_single_player() {
    close();
    GameView& game = GameView::GetInstance();
    game.SetMode(Mode::SinglePlayer);
    game.CreateSinglePlayerOverWorld();
    game.show();

}

void StartMenu::play_two_player() {
    close();
    GameView& game = GameView::GetInstance();
    game.SetMode(Mode::TwoPlayer);
    game.CreateTwoPlayerOverWorld();
    game.show();
}

void StartMenu::play_simulation() {
    close();
    GameView& game = GameView::GetInstance();
    game.SetMode(Mode::Simulation);
    game.CreateAIOverworld();
    game.show();
}
