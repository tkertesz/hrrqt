#include "car.h"

Car::Car(QGraphicsItem* parent) : QGraphicsItem(parent)
{
    carPict.load("debug/images/car.png");
    carPos = Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH/2;
}

QRectF Car::boundingRect() const{
    return QRectF(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT*2);
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(carPos,Settings::SCREEN_HEIGHT-(Settings::FIELD_HEIGHT*3),Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT*2,carPict);
    //painter->drawPixmap(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT*2,carPict);
}

//150*direction pixellel oldalra lépteti az autót
void Car::move(const short& direction){
    carPos += direction*Settings::FIELD_WIDTH;
}

QPainterPath Car::shape() const
{
    QPainterPath path;
    path.addRect(carPos,Settings::SCREEN_HEIGHT-(Settings::FIELD_HEIGHT*3),Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT*2);
    return path;
}
