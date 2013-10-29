#include "raceroadwidget.h"
#include "ui_raceroadwidget.h"

RaceRoadWidget::RaceRoadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RaceRoadWidget),
    vert(0), hori(1), life(10)
{
    road=generateRoad(1);
    ui->setupUi(this);
}

RaceRoadWidget::~RaceRoadWidget()
{
    delete ui;
}

/*void RaceRoadWidget::turnLeft()
{
    std::cout << "RaceCar turned left" << std::endl;
}

void RaceRoadWidget::turnRight()
{
    std::cout << "RaceCar turned right" << std::endl;
}*/

void RaceRoadWidget::play(){
//    RaceRoad();
//    represent();
//    short direction;
//    char ispressed(1);

//    bool running = true;
//    while(running){
//        direction=0;
//        switch(irInput.Event.KeyEvent.wVirtualKeyCode){
//            case VK_ESCAPE:
//                running = false;
//            break;
//            case VK_LEFT:
//            case VK_NUMPAD4:
//                direction=-1;
//                ispressed*=-1;
//            break;
//            case VK_RIGHT:
//            case VK_NUMPAD6:
//                direction=1;
//                ispressed*=-1;
//            break;
//        }
//        if(ispressed>0)moveCar(direction);
//        if(isHit()){
//            life--;
//            cout<<"ELET: "<<life<<endl;
//            //if(life<1)running=false;
//        }
//        represent();
//        sleep(1000);

//    }
}

void RaceRoadWidget::represent(){
    std::cout<<std::endl;
    for(unsigned short i(9);i<=9;i--){
        for(short j(0);j<3;j++){
            if(j==hori && i==vert){
                std::cout << 'A';
            }else{
                std::cout << road[i][j];
            }
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}

void RaceRoadWidget::moveCar(const short& direction){ //direction -1: bal, 1:jobb
    if(direction<0){
        if(hori>0){
            hori+=-1;
        }
    }else{
        if(hori<2){
            hori+=1;
        }
    }
}

std::vector<std::vector<unsigned char> > RaceRoadWidget::generateRoad(const int& difficulty){
    std::vector<std::vector<unsigned char> > idList;
    for(int i(0);i<10;i++){
        std::vector<unsigned char> idVec;
        for(int j(0);j<3;j++){
            if(rand()%100<30) idVec.push_back('1');
            else idVec.push_back('0');
        }
        idList.push_back(idVec);
    }
    return idList;
}

bool RaceRoadWidget::isHit(){
    if(vert<9){
        vert+=1;
    }else{
        road=generateRoad(1);
        vert=0;
    }
    return '1'==road[vert][hori];
}
