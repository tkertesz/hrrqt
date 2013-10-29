#include "raceroadwidget.h"
#include "ui_raceroadwidget.h"

RaceRoadWidget::RaceRoadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RaceRoadWidget)
{
    ui->setupUi(this);
}

RaceRoadWidget::~RaceRoadWidget()
{
    delete ui;
}

void RaceRoadWidget::turnLeft()
{
    std::cout << "RaceCar turned left" << std::endl;
}

void RaceRoadWidget::turnRight()
{
    std::cout << "RaceCar turned right" << std::endl;
}
