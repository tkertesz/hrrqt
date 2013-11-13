#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsItem>

class Road : public QGraphicsItem
{
private:
    const int ROAD_WIDTH = 672;
    const int ROAD_HEIGHT = 942;
    const int SCREEN_HEIGHT = 942/2;
    QPixmap roadPict;
    int roadCord;

public:
    Road(QGraphicsItem* parent = NULL);
    void roadStep();
protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;
};

#endif // ROAD_H
