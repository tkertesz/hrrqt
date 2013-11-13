#include "road.h"
#include <QtGui>

Road::Road(QGraphicsItem* parent) : QGraphicsItem(parent)
{
    roadCord = 0;
    roadPict.load("debug/images/newRoad.png");
}

QRectF Road::boundingRect() const{
    return QRectF(0,0,ROAD_WIDTH,SCREEN_HEIGHT);
}

void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0,roadCord,ROAD_WIDTH,ROAD_HEIGHT+roadCord,roadPict);
    //painter->drawRoundedRect(0,0,30,30,5,5);
}

void Road::roadStep(){
    roadCord-=10;
    if(roadCord+ROAD_HEIGHT<SCREEN_HEIGHT){
        roadCord=0;
    }
}
