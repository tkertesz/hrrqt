#ifndef RACEROADWIDGET_H
#define RACEROADWIDGET_H

#include <QWidget>
#include <QObject>
#include <iostream>
#include <vector>
#include <list>
#include <unistd.h>
#include <stdlib.h>
#include <QBasicTimer>
#include <mainwindow.h>

namespace Ui {
class RaceRoadWidget;
}

class RaceRoadWidget : public QWidget
{

    Q_OBJECT
    QBasicTimer timer;
    std::vector <std::vector<unsigned char> > road;
    unsigned short CarVCord;    // Autó függőleges koordinátája (0)
    unsigned short CarHCord;    // Autó vízszintes koordinátája (0,1,2)
    unsigned short life;        // Életek száma

    bool isHit();
    std::vector <std::vector<unsigned char> > generateRoad(const int& difficulty);
    Ui::RaceRoadWidget *ui;
    MainWindow *parent_window;

protected:
    void timerEvent(QTimerEvent *event);

public:
    static const unsigned int ROAD_SIZE=5;

    explicit RaceRoadWidget(QWidget *parent = 0);
    //void turnLeft();
    //void turnRight();
    ~RaceRoadWidget();

    void play();
    //void roadStep();
    void moveCar(const short& direction);
    void represent();
};

#endif // RACEROADWIDGET_H
