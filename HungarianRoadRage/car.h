#include <QGraphicsItem>
#include <QtGui>
#include <iostream>
#include "settings.h"

#ifndef CAR_H
#define CAR_H

class Car : public QGraphicsItem
{
    QPixmap carPict;        //Az autó képe
    int carPos;             //Az autó helye pixelekben

protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;

public:
    Car(QGraphicsItem* parent = NULL);
    QPainterPath shape() const;
    void move(const short& direction);                          //Az autó oldalirányú mozgatása
};

#endif // CAR_H
