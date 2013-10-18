#ifndef RaceRoad

#include "Player.hpp"
#include <vector>
#include <list>
#include <iostream>
#include <unistd.h>

using namespace std;

class RaceRoad{
    vector <vector<unsigned char> > road;
	unsigned short vert;
	unsigned short hori;
	unsigned short life;

	bool isHit();
    vector <vector<unsigned char> > generateRoad(const int& difficulty);
	void represent();
	
  public:
	RaceRoad();
	void play();
	//void roadStep();
	void moveCar(const short& direction);
	
};

#endif // !RaceRoad
