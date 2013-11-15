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
    const int bandwidth;
protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;

public:

    Car(QGraphicsItem* parent = NULL);
    void move(const short& direction);                          //Az autó oldalirányú mozgatása
};

#endif // CAR_H
