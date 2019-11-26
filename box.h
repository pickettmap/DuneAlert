#ifndef BOX_H
#define BOX_H
#include <QObject>
#include <QGraphicsItem>


class Box : public QObject, public QGraphicsItem
{
public:
    Box(int x, int y, int width, int height);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    int x_;
    int y_;
    int width_;
    int height_;
};

#endif // BOX_H
