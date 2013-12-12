#include "car.h"

// The car picture is from "debug/images/car.png", and the transform is the center of the car.
Car::Car(QGraphicsItem* parent) : QGraphicsItem(parent)
{
    carPict.load("debug/images/car.png");
    setTransformOriginPoint(Settings::FIELD_WIDTH/2,Settings::FIELD_HEIGHT);
}

// The rectangle is from (0,0) and Settings::FIELD_WIDTH width and twice Settings::FIELD_HEIGHT height.
QRectF Car::boundingRect() const
{
    return QRectF(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT*2);
}

//Draw the carPict.
void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT*2,carPict);

}

// The shape is from (20,44) to (Settings::FIELD_WIDTH-48,Settings::FIELD_HEIGHT*2-58).
QPainterPath Car::shape() const
{
    QPainterPath path;
    path.addRect(20,44,Settings::FIELD_WIDTH-48,Settings::FIELD_HEIGHT*2-58);
    return path;
}

//Set the is deg degree.
void Car::rotate(const int &deg)
{
    setRotation(deg);
}
