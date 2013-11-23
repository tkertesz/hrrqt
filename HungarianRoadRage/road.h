#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsWidget>
#include <QObject>
#include <QtGui>
#include <iostream>
#include "settings.h"
#include "car.h"
#include "pothole.h"
#include "roadgenerator.h"

class Road : public QGraphicsWidget
{
    Q_OBJECT

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
    explicit Road(QGraphicsWidget* parent = NULL);
    ~Road();

    void moveCar(const short& direction);   //Oldalra mozgatja az autót

signals:
    void sendLifeNumber(int life);
    void sendDistanceNumber(int distance);
    void stopGame(bool isWin);
};

#endif // ROAD_H
