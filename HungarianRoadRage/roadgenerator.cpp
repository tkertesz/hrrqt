#include "roadgenerator.h"

RoadGenerator::RoadGenerator()
{
    gate=1;
    readRoadFromFile("debug/roads/easyRoads.rds");
}

void RoadGenerator::readRoadFromFile(std::string fileName)
{

    // Create streamobject
    std::ifstream infile;
    infile.open(fileName);

    // Exit if file opening failed
    if (!infile.is_open()){
        std::cerr<<"Opening failed"<<std::endl;
        return;
    }

    // Start reading data
    bool idbool;
    while (!infile.eof()){
        roadSample roadSample;
        infile >> roadSample.in >> roadSample.out;
        for(int i=0; i<6; i++){
            std::vector<bool> idVec;
            for(int j=0; j<3; j++){
                infile >> idbool;
                idVec.push_back(idbool);
            }
            roadSample.road.push_back(idVec);
        }
        easyRoads.push_back(roadSample);
    }
    infile.close();
}

std::vector<std::vector<bool> > RoadGenerator::getRoad(unsigned short diff){
    roadSample idS;
    if(diff !=1 )return idS.road;
    bool good=false;
    int r(0);
    while(!good){
        r = rand()%easyRoads.size();
        if(easyRoads[r].in==gate)good=true;
    }
    gate=easyRoads[r].out;
    return easyRoads[r].road;
}
