#include "car.h"

//Betölti a képet
Car::Car(QGraphicsItem* parent) : QGraphicsItem(parent)
{
    carPict.load("debug/images/car.png");
}

//Két kockányi egység tartalmazza az autót
QRectF Car::boundingRect() const{
    return QRectF(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT*2);
}

//Kirajzolja az autót
void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT*2,carPict);
}

//Visszatér az autó széleivel
QPainterPath Car::shape() const
{
    QPainterPath path;
    path.addRect(5,10,Settings::FIELD_WIDTH-15,Settings::FIELD_HEIGHT*2-5);
    return path;
}
