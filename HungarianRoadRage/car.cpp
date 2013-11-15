#include "car.h"

Car::Car(QGraphicsItem* parent) : QGraphicsItem(parent),bandwidth(Settings::ROAD_WIDTH/4.5)
{
    carPict.load("debug/images/car.png");
    carPos = Settings::ROAD_WIDTH/2-Settings::CAR_WIDTH/2;
}

QRectF Car::boundingRect() const{
    return QRectF(0,0,Settings::CAR_WIDTH,Settings::CAR_HEIGHT);
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(carPos,Settings::SCREEN_HEIGHT-(Settings::CAR_HEIGHT*1.1),
                        Settings::CAR_WIDTH,Settings::CAR_HEIGHT,carPict);
}

//150*direction pixellel oldalra lépteti az autót
void Car::move(const short& direction){
    carPos += direction*bandwidth;
}
