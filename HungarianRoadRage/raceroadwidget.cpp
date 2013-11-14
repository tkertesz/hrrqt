#include "raceroadwidget.h"
#include "ui_raceroadwidget.h"

#include "mainwindow.h"

RaceRoadWidget::RaceRoadWidget(QWidget *parent) :
    QWidget(parent),
    CarVCord(0), CarHCord(1), life(10),
    ui(new Ui::RaceRoadWidget)
{
    road=generateRoad(1);
    ui->setupUi(this);
    //Two ways to call the closeVideoStream:
    //((MainWindow*)parentWidget())->closeVideoStream(); //not really good, but works
    parent_window = qobject_cast<MainWindow*>(parentWidget()); //best way :)
}

RaceRoadWidget::~RaceRoadWidget()
{
    delete ui;
    delete parent_window;
}


//Végigmegy a road vektoron és a kocsi helyére A-t ír, egyébként meg az adott értéket.
void RaceRoadWidget::represent(){
    //std::cout<<std::endl;
    for(unsigned short i(ROAD_SIZE-1);i<ROAD_SIZE;i--){
        for(short j(0);j<3;j++){
            if(j==CarHCord && i==CarVCord){
                std::cout << 'A';
            }else{
                std::cout << road[i][j];
            }
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}

//megváltoztatja a carHCord-ot, ha még benn van a pályán
void RaceRoadWidget::moveCar(const short& direction){ //direction -1: bal, 1:jobb
    if(direction<0){
        if(CarHCord>0){
            CarHCord+=-1;
        }
    }else{
        if(CarHCord<2){
            CarHCord+=1;
        }
    }
}

//véletlen számokkal generál ROAD_SIZE-méretű utat
std::vector<std::vector<unsigned char> > RaceRoadWidget::generateRoad(const int& difficulty){
    std::vector<std::vector<unsigned char> > idList;
    for(unsigned int i(0);i<ROAD_SIZE;i++){
        std::vector<unsigned char> idVec;
        for(int j(0);j<3;j++){
            if(rand()%100<30) idVec.push_back('1');
            else idVec.push_back('0');
        }
        idList.push_back(idVec);
    }
    std::cout << "Road generated with difficulty: " << difficulty <<std::endl;
    return idList;
}

// Ha a road vektor elég nagy kitörli az első sort, egyébként generál a végére hosszabbítást.
// Visszatér igazzal, ha az autó épp egyesen áll
bool RaceRoadWidget::isHit(){
    if(road.size()>ROAD_SIZE){
        road.erase(road.begin());
    }else{
        std::vector<std::vector<unsigned char> > idVec = generateRoad(0);
        road.insert(road.end(),idVec.begin(),idVec.end());
        road.erase(road.begin());
    }
    return '1'==road[CarVCord][CarHCord];
}

//Meghívja az isHit-et és a represent-et, megvizsgálja, hogy nem fogyott-e le az élet.
void RaceRoadWidget::timerEvent(QTimerEvent* event){
    if (event->timerId() == timer.timerId()) {
        if(isHit()){
            life--;
            std::cout<<"ELET: "<<life<<std::endl;
            if(life<1)
            {
                parent_window->closeVideoStream();
                parent_window->close();
                exit(0);

            }
        }
        represent();
    } else {
        QWidget::timerEvent(event);
    }
}

//Elindítja a timer-t.
void RaceRoadWidget::play()
{
    timer.start(1000, this);
    std::cerr << "Game started with this road:" <<std::endl;
    represent();
}
