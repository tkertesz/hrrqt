#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsItem>
#include <QObject>
#include <car.h>
#include <QBasicTimer>
#include <iostream>
#include <QBasicTimer>
#include <QtGui>

class Road : public QGraphicsItem
{
    QBasicTimer timer;
    std::vector <std::vector<unsigned char> > road; //Az utat reprezentálja, 0 út 1 a kátyú
    unsigned short carVCord;    // Autó függőleges koordinátája (0)
    unsigned short carHCord;    // Autó vízszintes koordinátája (0,1,2)
    unsigned short life;        // Életek száma
    int roadCord;               // Hol tart a pálya a mozgásban (hány pixel tűnt el a képernyő fölött
    QPixmap roadPict;           // A road képe
    Car* myCar;                 // Az autó

                                // Legenerálja a következő útszakaszt
    std::vector <std::vector<unsigned char> > generateRoad(const int& difficulty);

protected:
    void timerEvent(QTimerEvent *event);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;

public:
    static const int            ROAD_WIDTH = 672;                                   //Út és a képernyő szélessége
    static const int            ROAD_HEIGHT = 942;                                  //Út magassága
    static const int            SCREEN_HEIGHT = 700;                                //Képernyő magassága
    static const unsigned int   ROAD_SIZE = (int) SCREEN_HEIGHT/Car::CAR_HEIGHT;    //Hány koordináta fér el a képernyő hosszán

    Road(Car* car,QGraphicsItem* parent = NULL);

    bool isHit();                           //Lépteti a pályát konzolosan, megvizsgálja, hogy kátyúba lépett-e az autó
    void play();                            //Elindítja a játékot
    void moveCar(const short& direction);   //Oldalra mozgatja az autót
    void represent();                       //Kirajzolja a pályát a konzolra
    void roadStep();                        //Lépteti a pályát grafikusan
    unsigned short decreaseLife();          //Lecsökkenti az életet eggyel

};

#endif // ROAD_H
