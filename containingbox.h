#ifndef BOX_H
#define BOX_H
#include <QObject>
#include <QGraphicsItem>


class ContainingBox : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ContainingBox(int x, int y, int width, int height, QColor c, std::string text);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

signals:
    void onBoxClicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int x_;
    int y_;
    int width_;
    int height_;
    std::string text_;
    QColor color_;
};

#endif // BOX_H
