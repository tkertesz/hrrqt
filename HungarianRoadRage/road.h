#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsItem>
#include <iostream>
#include <QtGui>
#include "settings.h"
#include "car.h"
#include "pothole.h"
#include "roadgenerator.h"

class Road : public QGraphicsItem
{
    int life;                                   // Az autó életeinek a száma
    bool isDisplay;                             // Kiirattuk-e az életváltozást
    int distance;
    int speed;
    int accel;
    int moving;
    QPixmap roadPict;                           // A road képe
    Car* myCar;                                 // Az autó
    std::vector <Pothole*> potholes;            // A kátyúk vektora
    void generateRoad(const unsigned short& difficulty); // Legenerálja a következő útszakaszt
    void movePotholes();                        // A kátyúkat az elmozgatott útra helyezi
    RoadGenerator* roadGenerator;               // Az útgeneráló osztály

protected:
    void advance(int step);                     // Léptetés
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
                                                // Út kirajzolása
    QRectF boundingRect() const;                // Út mérete

public:
    Road(QGraphicsItem* parent = NULL);
    ~Road();

    void moveCar(const short& direction);   //Oldalra mozgatja az autót
};

#endif // ROAD_H
