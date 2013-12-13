#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsWidget>
#include <QObject>
#include <QtGui>
#include "settings.h"
#include "car.h"
#include "pothole.h"
#include "roadgenerator.h"

///Author: bendaf
class Road : public QGraphicsWidget
{
    Q_OBJECT

    int life;                                   // The number of the lifes.
    bool isLifeDisplayed;                       // Is the life number displayed.
    int distance;                               // How far is the car went.
    int speed;                                  // The speed of the car.
    int accel;                                  // The acceleration of the car.
    int moving;                                 // The remaind side direction moving.
    QPixmap roadPict;                           // The picture of the road.
    Car* myCar;                                 // The car.
    std::vector <Pothole*> potholes;            // The potholes.
                                                // Generate the next road section.
    void generateRoad(const unsigned short& difficulty);
    void movePotholes();                        // Move the potholes to the moved road.
    RoadGenerator* roadGenerator;               // The Road Generator.

protected:
    void advance(int step);                     // The animation function.
                                                // Draw the road.
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;                // The rectangle of the road.

public:                                         // Initialize
    explicit Road(QGraphicsWidget* parent = NULL);
    ~Road();                                    // Destruct
    void moveCar(const short& direction);       // The side shift of the car.

signals:
    void sendLifeNumber(const int& life);       // Send the number of lifes to the mainWindow.
    void sendDistanceNumber(const int& distance);//Send the distance to the mainWindow.
};

#endif // ROAD_H
