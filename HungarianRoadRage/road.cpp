#include "road.h"

//Beállítja a változókat
Road::Road(QGraphicsItem* parent) : QGraphicsItem(parent),
     life(10)
{
    setPos(0,Settings::SCREEN_HEIGHT-Settings::ROAD_HEIGHT+Settings::STEP_SIZE);
    myCar = new Car(this);
    myCar->setPos(Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH/2,
                  Settings::SCREEN_HEIGHT+Settings::FIELD_HEIGHT);
    generateRoad(0);
    roadPict.load("debug/images/road.png");

}

//Megadja a tartalmazó négyzet méretét, (igazából a graphicsview mérete)
QRectF Road::boundingRect() const{
    return QRectF(0,-Settings::SCREEN_HEIGHT,Settings::SCREEN_WIDTH,Settings::SCREEN_HEIGHT*2.5);
}

//Felrajzol két utat egymás után.
void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0,-Settings::ROAD_HEIGHT,Settings::SCREEN_WIDTH,Settings::ROAD_HEIGHT,roadPict);
    painter->drawPixmap(0,0,Settings::SCREEN_WIDTH,Settings::ROAD_HEIGHT,roadPict);
}

void Road::advance(int step){
    if(!step) return;
    setPos(0,pos().y()+Settings::STEP_SIZE);
    myCar->setPos(myCar->pos().x(),myCar->pos().y()-Settings::STEP_SIZE);
    if(pos().y()>Settings::SCREEN_HEIGHT){
        setPos(0,Settings::SCREEN_HEIGHT-Settings::ROAD_HEIGHT+Settings::STEP_SIZE);
        myCar->setPos(myCar->pos().x(),Settings::SCREEN_HEIGHT+Settings::FIELD_HEIGHT);
        generateRoad(1);
    }
    for(unsigned int i=0;i<potholes.size();i++){
        if(myCar->collidesWithItem(potholes[i])){
            life-=potholes[i]->conflict();
            std::cout<<"ELET: "<<life<<std::endl;
        }
    }
}

//Megváltoztatja a carHCord-ot, úgy, hogy ne lépjen le az útrlól
void Road::moveCar(const short& direction){ //direction -1: bal, 1:jobb
    if(direction==-1){
        if(myCar->pos().x()>Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH*1.5){
            myCar->setPos(myCar->pos().x()-Settings::FIELD_WIDTH,myCar->pos().y());
        }
    }else if(direction==1){
        if(myCar->pos().x()<Settings::SCREEN_WIDTH/2+Settings::FIELD_WIDTH*1.5){
            myCar->setPos(myCar->pos().x()+Settings::FIELD_WIDTH,myCar->pos().y());
        }
    }
}

//Véletlen számokkal generál ROAD_SIZE-méretű utat
void Road::generateRoad(const int& difficulty){
    for(unsigned int i(0);i<potholes.size();i++){
        potholes[i]->setParentItem(NULL);
    }
    for(unsigned int i(0);i<potholes.size();i++){
        delete potholes[i];
    }
    potholes.clear();
    if(difficulty!=0){
        for(int i=-(Settings::SCREEN_HEIGHT/Settings::FIELD_HEIGHT);i<Settings::ROAD_HEIGHT/Settings::FIELD_HEIGHT;i++){
            for(int j(0);j<3;j++){
                if(rand()%100<20) {
                    Pothole *idPot = new Pothole(this);
                    idPot->setPos(Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH*1.5+j*Settings::FIELD_WIDTH,i*Settings::FIELD_HEIGHT);
                    potholes.push_back(idPot);
                }
            }
        }
    }
    std::cout << potholes.size()<<" Road generated with difficulty: " << difficulty <<std::endl;
}

Road::~Road(){
    delete myCar;
    for(unsigned int i(0);i<potholes.size();i++){
        delete potholes[i];
    }
}
