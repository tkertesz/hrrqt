#include "car.h"

Car::Car(QGraphicsItem* parent) : QGraphicsItem(parent)
{
    carPict.load("debug/images/car.png");
}

QRectF Car::boundingRect() const{
    return QRectF(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT*2);
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT*2,carPict);
}

QPainterPath Car::shape() const
{
    QPainterPath path;
    path.addRect(0,0,Settings::FIELD_WIDTH-5,Settings::FIELD_HEIGHT*2);
    return path;
}
