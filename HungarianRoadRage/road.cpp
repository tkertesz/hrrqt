#include "road.h"

//Beállítja a változókat
Road::Road(Car* car,QGraphicsItem* parent) : QGraphicsItem(parent),
     carVCord(0), carHCord(1), life(10)
{
    myCar=car;
    roadCord = SCREEN_HEIGHT-ROAD_HEIGHT;
    road=generateRoad(1);
    roadPict.load("debug/images/road.png");
    setFlag(QGraphicsItem::ItemIsFocusable);
}

//Megadja a tartalmazó négyzet méretét
QRectF Road::boundingRect() const{
    return QRectF(0,0,ROAD_WIDTH,SCREEN_HEIGHT);
}

//Felrajzolja az utat
void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0,roadCord,ROAD_WIDTH,ROAD_HEIGHT,roadPict);
}

//Lépteti az utat
void Road::roadStep(){
    roadCord+=10;
    if(roadCord>0){
        roadCord=SCREEN_HEIGHT-ROAD_HEIGHT;
    }
    //std::cout<<ROAD_HEIGHT+roadCord<<"=?"<<ROAD_HEIGHT<<roadCord<<std::endl;
}

//Végigmegy a road vektoron és a kocsi helyére A-t ír, egyébként meg az adott értéket.
void Road::represent(){
    for(unsigned short i(ROAD_SIZE-1);i<ROAD_SIZE;i--){
        for(short j(0);j<3;j++){
            if(j==carHCord && i==carVCord){
                std::cout << 'A';
            }else{
                std::cout << road[i][j];
            }
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
    update();
}

//Megváltoztatja a carHCord-ot, ha még benn van a pályán
void Road::moveCar(const short& direction){ //direction -1: bal, 1:jobb
    if(direction<0){
        if(carHCord>0){
            carHCord+=-1;
            myCar->move(-1);
        }
    }else{
        if(carHCord<2){
            carHCord+=1;
            myCar->move(1);
        }
    }
}

//Véletlen számokkal generál ROAD_SIZE-méretű utat
std::vector<std::vector<unsigned char> > Road::generateRoad(const int& difficulty){
    std::vector<std::vector<unsigned char> > idList;
    for(unsigned int i(0);i<ROAD_SIZE;i++){
        std::vector<unsigned char> idVec;
        for(int j(0);j<3;j++){
            if(rand()%100<30) idVec.push_back('1');
            else idVec.push_back('0');
        }
        idList.push_back(idVec);
    }
    //std::cout << "Road generated with difficulty: " << difficulty <<std::endl;
    return idList;
}

// Ha a road vektor elég nagy kitörli az első sort, egyébként generál a végére hosszabbítást.
// Visszatér igazzal, ha az autó épp egyesen áll
bool Road::isHit(){
    if(road.size()>ROAD_SIZE){
        road.erase(road.begin());
    }else{
        std::vector<std::vector<unsigned char> > idVec = generateRoad(0);
        road.insert(road.end(),idVec.begin(),idVec.end());
        road.erase(road.begin());
    }
    return '1'==road[carVCord][carHCord];
}

// Kezeli a billentyűlenyomást
void Road::keyPressEvent(QKeyEvent *event){
    switch (event->key())
    {
        case Qt::Key_Right:
                moveCar(1); //turn right;
            break;
        case Qt::Key_Left:
                moveCar(-1); //turn left;
            break;
        case Qt::Key_Escape:
            exit(0);
            break;
        default:
            break;
    }
}

//Lecsökkenti az életet egyel, visszaadja a megmaradt életek számát
unsigned short Road::decreaseLife(){
    std::cout<<"ELET: "<<life<<std::endl;
    return --life;
}
