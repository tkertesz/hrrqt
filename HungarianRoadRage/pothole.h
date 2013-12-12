#include <QGraphicsItem>
#include <QtGui>
#include "settings.h"

#ifndef POTHOLE_H
#define POTHOLE_H

///Author: bendaf
class Pothole : public QGraphicsItem
{
    QPixmap potholePict;    // The picture of the pothole.
    unsigned short depth;   // The depth of the pothole.

protected:
                                    // Draw the pothole with the painter.
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;    // The rectangle which is refreshed by the paint function.

public:
    Pothole(QGraphicsItem* parent = NULL);  // Load the picture of the car and add a random rotation to the pothole.
    QPainterPath shape() const;             // Return a path where the pothole is conlict.
    unsigned short conflict();              // Return the number of injury it's caused.
};

#endif // POTHOLE_H
