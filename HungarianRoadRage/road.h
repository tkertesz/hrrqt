#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsItem>
#include <iostream>
#include <QtGui>
#include "settings.h"
#include "car.h"
#include "pothole.h"

class Road : public QGraphicsItem
{
    int life;                       // Az autó életeinek a száma
    QPixmap roadPict;               // A road képe
    Car* myCar;                     // Az autó
    std::vector <Pothole*> potholes;// A kátyúk vektora
    void generateRoad(const int& difficulty);
                                    // Legenerálja a következő útszakaszt

protected:
    void advance(int step);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;

public:
    Road(QGraphicsItem* parent = NULL);
    ~Road();

    void moveCar(const short& direction);   //Oldalra mozgatja az autót
};

#endif // ROAD_H
