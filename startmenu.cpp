#include "startmenu.h"
#include "gameview.h"

#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

StartMenu::StartMenu(QWidget *parent)
{
    GameView& game = GameView::GetInstance();
    QGraphicsScene *scene = game.scene;
    QLabel *title = new QLabel("DUNEALERT",this);
    title->setAlignment(Qt::AlignHCenter);
    QLabel *title2 = new QLabel("DUNEALERT",this);
    title2->setAlignment(Qt::AlignHCenter);

    QPushButton *play_btn = new QPushButton("Play", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addWidget(title2);
    layout->addWidget(play_btn);

    connect(play_btn,SIGNAL(clicked()),this,SLOT(play()));

    setLayout(layout);

}


void StartMenu::play() {

    GameView& game = GameView::GetInstance();
    //game.showFullScreen();
    game.show();
    close();

}
