#include "pothole.h"

//Betölti a képet
Pothole::Pothole(QGraphicsItem* parent): QGraphicsItem(parent),depth(1)
{
    potholePict.load("debug/images/pothole.png");
}

//Egy kocka tartalmazza a kátyút
QRectF Pothole::boundingRect() const{
    return QRectF(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT);
}

//Kirajzolja a kátyút
void Pothole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT,potholePict);
}

//Visszatér a kátyú széleivel
QPainterPath Pothole::shape() const
{
    QPainterPath path;
    path.addRect(0,0,Settings::FIELD_WIDTH-20,Settings::FIELD_HEIGHT-25);
    return path;
}

//Ha ütközik az autóval visszatér 1-el ha már ütközött vele az autó visszatér 0-val.
unsigned short Pothole::conflict(){
    if(depth--<=0)return 0;
    return 1;
}
