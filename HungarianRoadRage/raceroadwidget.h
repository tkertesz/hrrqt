#ifndef RACEROADWIDGET_H
#define RACEROADWIDGET_H

#include <QWidget>
#include <iostream>

namespace Ui {
class RaceRoadWidget;
}

class RaceRoadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RaceRoadWidget(QWidget *parent = 0);
    void turnLeft();
    void turnRight();
    ~RaceRoadWidget();

private:
    Ui::RaceRoadWidget *ui;
};

#endif // RACEROADWIDGET_H
