#include "car.h"

//Betölti a képet
Car::Car(QGraphicsItem* parent) : QGraphicsItem(parent)
{
    carPict.load("debug/images/car.png");
    setTransformOriginPoint(Settings::FIELD_WIDTH/2,Settings::FIELD_HEIGHT);
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
    path.addRect(20,44,Settings::FIELD_WIDTH-48,Settings::FIELD_HEIGHT*2-58);
    return path;
}

void Car::rotate(int deg){
    //std::cout<<transformOriginPoint().rx()<<" "<<transformOriginPoint().ry()<<std::endl;
    setRotation(deg);
}
