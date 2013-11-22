#include "road.h"

//Beállítja a változókat
Road::Road(QGraphicsWidget* parent) : QGraphicsWidget(parent),
    life(Settings::STARTLIFE),isDisplay(false),distance(0),speed(Settings::STEP_SIZE),
    accel(0),moving(0)
{
    setPos(0,Settings::SCREEN_HEIGHT-Settings::ROAD_HEIGHT);
    myCar = new Car(this);
    myCar->setPos(Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH/2,
                  Settings::ROAD_HEIGHT-(Settings::FIELD_HEIGHT*3));
    myCar->setZValue(2);
    generateRoad(0);
    roadPict.load("debug/images/road.png");
    roadGenerator = new RoadGenerator();
}

//Megadja a tartalmazó négyzet méretét
QRectF Road::boundingRect() const{
    return QRectF(0,-Settings::SCREEN_HEIGHT,Settings::SCREEN_WIDTH,Settings::SCREEN_HEIGHT*2.5);
}

//Felrajzol két utat egymás után.
void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0,-Settings::ROAD_HEIGHT,Settings::SCREEN_WIDTH,Settings::ROAD_HEIGHT,roadPict);
    painter->drawPixmap(0,0,Settings::SCREEN_WIDTH,Settings::ROAD_HEIGHT,roadPict);
}

//Animációért felelős
void Road::advance(int step){
    if(!step) return;   //ha step 0, akkor nem csinál semmit
    moveBy(0,speed);          //lépteti az utat és a kocsit
    myCar->moveBy(0,-speed);
    if(moving>0){
        moving-=speed;
        myCar->moveBy(speed,0);
    }
    if(moving<0){
        moving+=speed;
        myCar->moveBy(-speed,0);
    }
    accel++;
    //sendDistanceNumber(accel);
    distance+=speed/5;
    if(accel>100){
        accel=0;
        speed=speed*1.3;
        std::cout<<"TÁVOLSÁG: "<<distance<<std::endl;
    }
    if(pos().y()>Settings::SCREEN_HEIGHT){  //ha az út kiment a képernyőről újra beállítja a koordinátákat
        moveBy(0,-Settings::ROAD_HEIGHT);
        myCar->moveBy(0,Settings::ROAD_HEIGHT);
        movePotholes();
        generateRoad(1);                    //generál egy új kátyúsort
    }
                                            //ha az autó ütközik egy kátyúval csökkenti az életét.
    for(unsigned int i=0;i<potholes.size();i++){
        if(myCar->collidesWithItem(potholes[i])){
            int depth=potholes[i]->conflict();
            if(depth>0){
                speed=Settings::STEP_SIZE;
                accel=0;
                life-=depth;
                emit sendLifeNumber(life);
                isDisplay=false;
                if(life<0){
                    std::cout<<"HALÁL!"<<std::endl;
                    //exit(0);
                }
            }
            if(!isDisplay){
                std::cout<<"ELET: "<<life<<std::endl;
                isDisplay=true;
            }
        }
    }
}

//Lépteti az autót oldalra, úgy, hogy ne lépjen le az útrlól
///TODO: még jobbra le tud lépni a tesztelés érdekében!
void Road::moveCar(const short& direction){ //direction -1: bal, 1:jobb
    if(direction==-1){
        if(myCar->pos().x()+moving>Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH*0.5){
            moving+=-Settings::FIELD_WIDTH;
            //myCar->moveBy(-Settings::FIELD_WIDTH,0);
        }
    }else if(direction==1){
        if(myCar->pos().x()+moving<Settings::SCREEN_WIDTH/2+Settings::FIELD_WIDTH*1.5){
            moving+=Settings::FIELD_WIDTH;
            //myCar->moveBy(Settings::FIELD_WIDTH,0);
        }
    }
}

//Véletlen számokkal generál ROAD_SIZE-méretű utat
void Road::generateRoad(const unsigned short& difficulty){
    if(difficulty==0)return;
    std::vector<std::vector<bool> > idRoad = roadGenerator->getRoad(difficulty);
    for(unsigned int i=0;i<idRoad.size();i++){
        for(unsigned int j=0;j<idRoad[i].size();j++){
            if(idRoad[i][j] == true){
                Pothole *idPot = new Pothole(this);
                idPot->setPos(Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH*1.5+j*Settings::FIELD_WIDTH,-(int)(i+1)*Settings::FIELD_HEIGHT);
                idPot->setZValue(1);
                potholes.push_back(idPot);
            }
        }
    }
    //std::cout <<"Road generated with difficulty: " << difficulty <<std::endl;
}

Road::~Road(){
    delete myCar;
    for(unsigned int i(0);i<potholes.size();i++){
        delete potholes[i];
    }
}

//A már nem kellő kátyúkat törli, a még kellőket pedig áthelyezi, hogy a képernyőn maradjon törlésnél.
void Road::movePotholes(){
    auto i = std::begin(potholes);
    while (i != std::end(potholes)) {
        if((*i)->pos().y()>0){  //Törlés
            (*i)->hide();
            i = potholes.erase(i);
        }else{                  //Léptetés
            (*i)->moveBy(0,Settings::ROAD_HEIGHT);
            i++;
        }
    }
}
