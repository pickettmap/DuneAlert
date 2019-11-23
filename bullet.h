#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>
#include <QGraphicsItem>


class Bullet: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet();
public slots:
    void travel();
};

#endif // BULLET_H
