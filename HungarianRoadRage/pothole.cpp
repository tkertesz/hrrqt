#include "pothole.h"

Pothole::Pothole(QGraphicsItem* parent): QGraphicsItem(parent),depth(1)
{
    potholePict.load("debug/images/pothole.png");
}

QRectF Pothole::boundingRect() const{
    return QRectF(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT);
}

void Pothole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT,potholePict);
}

QPainterPath Pothole::shape() const
{
    QPainterPath path;
    path.addRect(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT);
    return path;
}

unsigned short Pothole::conflict(){
    if(depth<=0)return 0;
    return depth--;
}
