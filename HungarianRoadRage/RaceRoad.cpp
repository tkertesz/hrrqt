/*#include "RaceRoad.hpp"

RaceRoad::RaceRoad()
{
	road=generateRoad(1);
    hori=1;
    vert=0;
    life=10;
}

void RaceRoad::play(){
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

void RaceRoad::represent(){
	cout<<endl;
	for(unsigned short i(9);i<=9;i--){
		for(short j(0);j<3;j++){
			if(j==hori && i==vert){
				cout << 'A';
			}else{
				cout << road[i][j];
			}
		}
		cout << endl;
	}
	cout<<endl;
}

void RaceRoad::moveCar(const short& direction){
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

vector<vector<unsigned char> > RaceRoad::generateRoad(const int& difficulty){
    vector<vector<unsigned char> > idList;
	for(int i(0);i<10;i++){
		vector<unsigned char> idVec;
		for(int j(0);j<3;j++){
			if(rand()%100<30) idVec.push_back('1');
			else idVec.push_back('0');
		}
		idList.push_back(idVec);
	}
	return idList;
}

bool RaceRoad::isHit(){
	if(vert<9){
		vert+=1;
	}else{
		road=generateRoad(1);
		vert=0;
	}
	return '1'==road[vert][hori];
}*/
