#include "pothole.h"

//vCord: 0 to ROAD_SIZE
//hCord: 0 to 2
Pothole::Pothole(int vCord, int hCord, QGraphicsItem* parent):
    QGraphicsItem(parent), potholeVPos(vCord*Settings::FIELD_HEIGHT),
    potholeHPos(Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH*1.5+hCord*Settings::FIELD_WIDTH)
{
    potholePict.load("debug/images/pothole.png");
}

QRectF Pothole::boundingRect() const{
    return QRectF(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT);
}

void Pothole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(potholeHPos,potholeVPos,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT,potholePict);
}

bool Pothole::step(unsigned int pixels){
    potholeVPos+=pixels;
    return potholeVPos>Settings::SCREEN_HEIGHT;
}

QPainterPath Pothole::shape() const
{
    QPainterPath path;
    path.addRect(potholeHPos,potholeVPos,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT);
    return path;
}
