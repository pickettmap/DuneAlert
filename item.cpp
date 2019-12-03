#include "item.h"
#include "gameview.h"
#include "player.h"

Item::Item()
{
}

void Item::use()
{
    //handled in derived classes
}

void mousePressEvent (QGraphicsSceneMouseEvent *event)
{
//    if(event->button() == Qt::LeftButton)
//    {
//        GameView& game = GameView::GetInstance();
//        game.get_player()
//    }
}
