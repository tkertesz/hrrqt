#include <QGraphicsItem>
#include <QtGui>
#include <iostream>
#include "settings.h"

#ifndef POTHOLE_H
#define POTHOLE_H

class Pothole : public QGraphicsItem
{
    QPixmap potholePict;        //A kátyú képe
    int potholeVPos;            //A kátyú függőleges helye pixelben
    int potholeHPos;            //A kátyú vízszintes helye pixelben

protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;

public:
    Pothole(int Vcord, int Hcord, QGraphicsItem* parent = NULL);
    QPainterPath shape() const;
    bool step(unsigned int pixels = 10);
};

#endif // POTHOLE_H
