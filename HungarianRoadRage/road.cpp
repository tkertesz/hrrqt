#include "road.h"

//Beállítja a változókat
Road::Road(QGraphicsItem* parent) : QGraphicsItem(parent),
     life(10)
{
    setPos(0,Settings::SCREEN_HEIGHT-Settings::ROAD_HEIGHT+Settings::STEP_SIZE);
    myCar = new Car(this);
    myCar->setPos(Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH/2,
                  Settings::SCREEN_HEIGHT+Settings::FIELD_HEIGHT);
    myCar->setZValue(2);
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
    moveBy(0,Settings::STEP_SIZE);
    myCar->moveBy(0,-Settings::STEP_SIZE);
    if(pos().y()>Settings::SCREEN_HEIGHT){
        moveBy(0,-Settings::ROAD_HEIGHT+Settings::STEP_SIZE);
        myCar->moveBy(0,Settings::ROAD_HEIGHT-Settings::STEP_SIZE);
        movePotholes();
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
    if(difficulty!=0){
        for(int i=-(Settings::SCREEN_HEIGHT/Settings::FIELD_HEIGHT);i<0;i++){
            for(int j(0);j<3;j++){
                if(rand()%100<20) {
                    Pothole *idPot = new Pothole(this);
                    idPot->setPos(Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH*1.5+j*Settings::FIELD_WIDTH,i*Settings::FIELD_HEIGHT);
                    idPot->setZValue(1);
                    potholes.push_back(idPot);
                }
            }
        }
    }
    std::cout <<" Road generated with difficulty: " << difficulty <<std::endl;
}

Road::~Road(){
    delete myCar;
    for(unsigned int i(0);i<potholes.size();i++){
        delete potholes[i];
    }
}

void Road::movePotholes(){
    auto i = std::begin(potholes);
    while (i != std::end(potholes)) {
        //std::cout<<"Pos: ("<<((*i)->pos().x()-89.5)/107<<", "<<(*i)->pos().y()/Settings::FIELD_HEIGHT<<")";
        if((*i)->pos().y()>0){
            (*i)->hide();
            //std::cout<<" erase";
            i = potholes.erase(i);
        }else{
            (*i)->moveBy(0,Settings::ROAD_HEIGHT-Settings::STEP_SIZE);
            //std::cout<<" new coordinate: ("<<((*i)->pos().x()-89.5)/107<<", "<<(*i)->pos().y()/Settings::FIELD_HEIGHT<<")";
            i++;
        }
        //std::cout<<std::endl;
    }
}
