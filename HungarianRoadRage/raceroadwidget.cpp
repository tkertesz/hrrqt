#include "raceroadwidget.h"
#include "ui_raceroadwidget.h"

#include "mainwindow.h"

RaceRoadWidget::RaceRoadWidget(QWidget *parent) :
    QWidget(parent),
    vert(0), hori(1), life(10),
    ui(new Ui::RaceRoadWidget)
{
    road=generateRoad(1);
    ui->setupUi(this);
    timer.start(1000, this);
    represent();
}

RaceRoadWidget::~RaceRoadWidget()
{
    delete ui;
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
    if(road.size()>9){
        road.erase(road.begin());
    }else{
        std::vector<std::vector<unsigned char> > idVec = generateRoad(0);
        road.insert(road.end(),idVec.begin(),idVec.end());
    }
    return '1'==road[vert][hori];
}

void RaceRoadWidget::timerEvent(QTimerEvent* event){
    if (event->timerId() == timer.timerId()) {
        if(isHit()){
            life--;
            std::cout<<"ELET: "<<life<<std::endl;
            if(life<1)
            {
                exit(0);
                //Two ways to call the closeVideoStream:
                //((MainWindow*)parentWidget())->closeVideoStream(); //not really good, but works
                MainWindow *parent_window = qobject_cast<MainWindow*>(parentWidget()); //best way :)
                parent_window->closeVideoStream();

            }
        }
        represent();
    } else {
        QWidget::timerEvent(event);
    }
}
