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
    std::vector <std::vector<unsigned char> > road; //Az utat reprezentálja, 0 út 1 a kátyú
    unsigned short carVCord;        // Autó függőleges koordinátája (1, de kettő magas!)
    unsigned short carHCord;        // Autó vízszintes koordinátája (0,1,2)
    unsigned short life;            // Életek száma
    int roadCord;                   // Hol tart a pálya a mozgásban (hány pixel tűnt el a képernyő fölött
    QPixmap roadPict;               // A road képe
    QPixmap roadPict2;              // Az út második képe
    Car* myCar;                     // Az autó
    std::vector <Pothole*> potholes;// A kátyúk vektora
    std::vector <std::vector<unsigned char> > generateRoad(const int& difficulty);
                                    // Legenerálja a következő útszakaszt

protected:
    void timerEvent(QTimerEvent *event);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;

public:
    Road(Car* car,QGraphicsItem* parent = NULL);
    ~Road();

    bool isHit();                           //Lépteti a pályát konzolosan, megvizsgálja, hogy kátyúba lépett-e az autó
    void play();                            //Elindítja a játékot
    void moveCar(const short& direction);   //Oldalra mozgatja az autót
    void represent();                       //Kirajzolja a pályát a konzolra
    void roadStep(unsigned int pixels = 10);                        //Lépteti a pályát grafikusan
    unsigned short decreaseLife();          //Lecsökkenti az életet eggyel

};

#endif // ROAD_H
