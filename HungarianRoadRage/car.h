#include <QGraphicsItem>
#include <QtGui>
#include "settings.h"

#ifndef CAR_H
#define CAR_H

///Author: bendaf
class Car : public QGraphicsItem
{
    QPixmap carPict;        // The picture of the car.

protected:
                                        // Draw the car with the painter.
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;        // The rectangle which is refreshed by the paint function.

public:
    Car(QGraphicsItem* parent = NULL);  // Load the picture of the car, and set the transform.
    QPainterPath shape() const;         // The shape that contains the "bottom" of the car (where can conflict).
    void rotate(const int& deg);        // Set the rotation of the car.
};

#endif // CAR_H
