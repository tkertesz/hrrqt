#include "road.h"

//Beállítja a változókat
Road::Road(QGraphicsItem* parent) : QGraphicsItem(parent),
     life(10),isDisplay(false)
{
    setPos(0,Settings::SCREEN_HEIGHT-Settings::ROAD_HEIGHT+Settings::STEP_SIZE);
    myCar = new Car(this);
    myCar->setPos(Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH/2,
                  Settings::ROAD_HEIGHT-(Settings::FIELD_HEIGHT*3));
    myCar->setZValue(2);
    generateRoad(0);
    roadPict.load("debug/images/road.png");
    std::cout<<Settings::ROAD_SIZE<<std::endl;

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
    moveBy(0,Settings::STEP_SIZE);          //lépteti az utat és a kocsit
    myCar->moveBy(0,-Settings::STEP_SIZE);
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
                life-=depth;
                isDisplay=false;
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
        if(myCar->pos().x()>Settings::SCREEN_WIDTH/2-Settings::FIELD_WIDTH*0.5){
            myCar->moveBy(-Settings::FIELD_WIDTH,0);
        }
    }else if(direction==1){
        if(myCar->pos().x()<Settings::SCREEN_WIDTH/2+Settings::FIELD_WIDTH*1.5){
            myCar->moveBy(Settings::FIELD_WIDTH,0);
        }
    }
}

//Véletlen számokkal generál ROAD_SIZE-méretű utat
///TODO ezt még ki kell fejleszteni!
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
    std::cout <<"Road generated with difficulty: " << difficulty <<std::endl;
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
