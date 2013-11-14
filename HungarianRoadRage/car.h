#ifndef CAR_H
#define CAR_H

#include <QGraphicsItem>

class Car : public QGraphicsItem
{
    QPixmap carPict;        //Az autó képe
    int carPos;             //Az autó helye pixelekben

protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;

public:
    static const int CAR_WIDTH = 145;       //Az autó szélessége
    static const int CAR_HEIGHT = 248;      //Az autó magassága

    Car(QGraphicsItem* parent = NULL);
    void move(const short& direction);      //Az autó oldalirányú mozgatása
};

#endif // CAR_H
