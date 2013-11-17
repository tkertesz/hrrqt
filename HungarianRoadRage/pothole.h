#include <QGraphicsItem>
#include <QtGui>
#include <iostream>
#include "settings.h"

#ifndef POTHOLE_H
#define POTHOLE_H

class Pothole : public QGraphicsItem
{
    QPixmap potholePict;    //A kátyú képe
    unsigned short depth;   //A kátyú mélysége

protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;

public:
    Pothole(QGraphicsItem* parent = NULL);
    QPainterPath shape() const;
    unsigned short conflict();
};

#endif // POTHOLE_H
