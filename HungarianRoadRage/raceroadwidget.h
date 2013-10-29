#ifndef RACEROADWIDGET_H
#define RACEROADWIDGET_H

#include <QWidget>
#include <iostream>
#include <vector>
#include <list>
#include <unistd.h>
#include <stdlib.h>
#include <QBasicTimer>

namespace Ui {
class RaceRoadWidget;
}

class RaceRoadWidget : public QWidget
{
    Q_OBJECT
    QBasicTimer timer;
    std::vector <std::vector<unsigned char> > road;
    unsigned short vert;
    unsigned short hori;
    unsigned short life;

    bool isHit();
    std::vector <std::vector<unsigned char> > generateRoad(const int& difficulty);
    Ui::RaceRoadWidget *ui;
protected:
    void timerEvent(QTimerEvent *event);

public:
    explicit RaceRoadWidget(QWidget *parent = 0);
    void turnLeft();
    void turnRight();
    ~RaceRoadWidget();

    void play();
    //void roadStep();
    void moveCar(const short& direction);
    void represent();

};

#endif // RACEROADWIDGET_H
