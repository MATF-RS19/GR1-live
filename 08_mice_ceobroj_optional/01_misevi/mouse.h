#ifndef MOUSE_H
#define MOUSE_H

#include <QGraphicsItem>

class Mouse : public QGraphicsItem {
public:
    Mouse();

    // pure virtual function
    // Returns an estimate of the area painted by the item
    QRectF boundingRect() const override;

    // Returns the accurate shape of the mouse item
    QPainterPath shape() const override;

    // pure virtual function
    // draws the item
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;

protected:
    // Handling animation
    void advance(int step) override;

private:
    qreal angle;
    qreal speed;
    qreal mouseEyeDirection;

    QColor color;
};

#endif
