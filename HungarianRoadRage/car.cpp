#include "car.h"
#include "road.h"
#include <QtGui>
#include <iostream>

Car::Car(QGraphicsItem* parent) : QGraphicsItem(parent)
{
    carPict.load("debug/images/car.png");
    carPos = 265;
}

QRectF Car::boundingRect() const{
    return QRectF(0,0,CAR_WIDTH,CAR_HEIGHT);
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(carPos,Road::SCREEN_HEIGHT-(CAR_HEIGHT*1.1),CAR_WIDTH,CAR_HEIGHT,carPict);
}

//150*direction pixellel oldalra lépteti az autót
void Car::move(const short& direction){
    carPos += direction*150;
}
