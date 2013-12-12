#include "road.h"

// Initialize life, isLifeDisplayed, distance, speed, accel, moving, myCar, roadGenerator,
// set the start position of the road, load the road picture from "debug/images/road.png"
// and generate the first road.
Road::Road(QGraphicsWidget* parent) : QGraphicsWidget(parent),
    life(Settings::STARTLIFE),isLifeDisplayed(false),distance(0),speed(Settings::STEP_SIZE),
    accel(0),moving(0)
{
    myCar = new Car(this);
    myCar->setPos(Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH/2,
                  Settings::ROAD_HEIGHT-(Settings::FIELD_HEIGHT*3));
    myCar->setZValue(2);
    roadGenerator = new RoadGenerator();
    setPos(0,Settings::SCREEN_HEIGHT-Settings::ROAD_HEIGHT);
    roadPict.load("debug/images/road.png");
    generateRoad(0);
}

// The rectangle is from (0,-Settings::SCREEN_HEIGHT) to
// (Settings::SCREEN_WIDTH,Settings::SCREEN_HEIGHT*2.5) because from the road moving.
QRectF Road::boundingRect() const
{
    return QRectF(0,-Settings::SCREEN_HEIGHT,Settings::SCREEN_WIDTH,
                  Settings::SCREEN_HEIGHT*2.5);
}

// Drow 2 roads one and after.
void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,-Settings::ROAD_HEIGHT,Settings::SCREEN_WIDTH,
                        Settings::ROAD_HEIGHT,roadPict);
    painter->drawPixmap(0,0,Settings::SCREEN_WIDTH,Settings::ROAD_HEIGHT,roadPict);
}

// Do the animating.
void Road::advance(int step)
{

    // if the step is 0 then return.
    if(!step) return;

    // -- move the road and the car --
    moveBy(0,speed);
    myCar->moveBy(0,-speed);
    if(moving-speed>0)              // move the car by speed to the right and set rotate.
    {
        moving-=speed;
        myCar->moveBy(speed,0);
        myCar->rotate(5);
    }
    else if(moving+speed<0)         // move the car by speed to the left and set rotate.
    {
        moving+=speed;
        myCar->moveBy(-speed,0);
        myCar->rotate(-5);
    }
    else                            // move the car by moving and set the rotate 0.
    {
        myCar->moveBy(moving,0);
        moving=0;
        myCar->rotate(0);
    }

    // -- manage acceleration, distance, and speed --
    accel++;                                        // increase acceleration.
    distance+=qRound( (double) speed/5);            // increase distance.
    if(accel>100)                                   // reset accel, increase speed.
    {
        accel=0;
        if(speed<14)speed=qRound((double)speed+2);
        emit sendDistanceNumber(distance);          // send distance to the mainWindow.
    }

    // -- manage road moving --
    if(pos().y()>Settings::SCREEN_HEIGHT)           // reset the the road, the car and the potholes.
    {
        moveBy(0,-Settings::ROAD_HEIGHT);
        myCar->moveBy(0,Settings::ROAD_HEIGHT);
        movePotholes();
        generateRoad(1);                            // generate new road.
    }

    // -- manage collision --
    for(unsigned int i=0;i<potholes.size();i++)
    {
        if(myCar->collidesWithItem(potholes[i]))
        {
            int depth=potholes[i]->conflict();
            if(depth>0)                             // reset speed, acceleration, decrease life.
            {
                speed=Settings::STEP_SIZE;
                accel=0;
                life-=depth;
                isLifeDisplayed=false;          // the new life number is not displayed.
                if(life<0)
                {
                    emit stopGame();            // stop the game.
                }
            }
            if(!isLifeDisplayed)
            {
                emit sendLifeNumber(life);      // send the life number to mainWindow.
                isLifeDisplayed=true;           // the new lifenumber is displayed.
            }
        }
    }
}

// Side shift the car, if direction is -1 than to the left side, if 1 to the right
// but only if it's still in the road.
///TODO: még jobbra le tud lépni a tesztelés érdekében!
void Road::moveCar(const short& direction)
{
    if(direction==-1)
    {
        if(myCar->pos().x() + moving>Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH*0.5)
        {
            moving+=-Settings::FIELD_WIDTH;
        }
    }
    else if(direction==1)
    {
        if(myCar->pos().x() + moving<Settings::SCREEN_WIDTH/2+Settings::FIELD_WIDTH*1.5)
        {
            moving+=Settings::FIELD_WIDTH;
        }
    }
}

// Generate the new road with difficulty.
void Road::generateRoad(const unsigned short& difficulty)
{
    if(difficulty==0)return;
    std::vector<std::vector<bool> > idRoad = roadGenerator->getRoad(difficulty);
    for(unsigned int i=0;i<idRoad.size();i++)           // generate the potholes.
    {
        for(unsigned int j=0;j<idRoad[i].size();j++)
        {
            if(idRoad[i][j] == true)
            {
                Pothole *idPot = new Pothole(this);
                idPot->setPos(
                       Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH*1.5+j*Settings::FIELD_WIDTH,
                       -(int)(i+1)*Settings::FIELD_HEIGHT);
                idPot->setZValue(1);
                potholes.push_back(idPot);
            }
        }
    }
}

// Delete myCar, roadgenerator and potholes.
Road::~Road()
{
    delete myCar;
    for(unsigned int i(0);i<potholes.size();i++)
    {
        delete potholes[i];
    }
    delete roadGenerator;
}

//Move the potholes when moved the road.
void Road::movePotholes()
{
    auto i = std::begin(potholes);
    while (i != std::end(potholes))
    {
        if((*i)->pos().y()>0)   // If it's not in the screen delete.
        {
            (*i)->hide();
            i = potholes.erase(i);
        }
        else                    // else move to it's new position.
        {
            (*i)->moveBy(0,Settings::ROAD_HEIGHT);
            i++;
        }
    }
}
