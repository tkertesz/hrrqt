#include "pothole.h"

// The pothole picture is from "debug/images/pothole.png", and a random rotation add.
Pothole::Pothole(QGraphicsItem* parent): QGraphicsItem(parent),depth(1)
{
    potholePict.load("debug/images/pothole.png");
    setTransformOriginPoint(Settings::FIELD_WIDTH/2,Settings::FIELD_HEIGHT/2);
    setRotation(rand()%360);
}

// The rectangle is from (0,0) to (Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT).
QRectF Pothole::boundingRect() const
{
    return QRectF(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT);
}

//Draw the potholePict.
void Pothole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,Settings::FIELD_WIDTH,Settings::FIELD_HEIGHT,potholePict);
}

// The path is an ellipse with center (53,50) and 43 width and 35 height.
QPainterPath Pothole::shape() const
{
    QPainterPath path;
    path.addEllipse(QPointF(53,50),43,35);
    return path;
}

//Return the depth and decrease it if it's bigger than 0.
unsigned short Pothole::conflict()
{
    if(depth>0)
    {
        depth--;
        return 1;
    }
    return 0;
}
