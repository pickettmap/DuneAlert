#ifndef FINALGRAPH_H
#define FINALGRAPH_H
#include <QObject>
#include <QGraphicsItem>


class FinalGraph: public QObject, public QGraphicsItem
{
public:
    FinalGraph(int height, int x, int y, QColor c);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void setHeight(int height) { height_ = height; }

private:
    int x_;
    int y_;
    int width_ = 20;
    int height_;
    QColor color_;
};

#endif // FINALGRAPH_H
