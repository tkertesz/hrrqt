#include "roadgenerator.h"

RoadGenerator::RoadGenerator()
{
    gate=1;
    readRoadFromFile("debug/roads/easyRoads.rds",1);
    readRoadFromFile("debug/roads/normalRoads.rds",2);
}

void RoadGenerator::readRoadFromFile(std::string fileName,int diff)
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
        if(diff==1){
            easyRoads.push_back(roadSample);
        }else if(diff==2){
            normalRoads.push_back(roadSample);
        }
    }
    infile.close();
}

std::vector<std::vector<bool> > RoadGenerator::getRoad(unsigned short diff){
    bool good=false;
    int r(0);
    if(diff == 1){
        while(!good){
            r = rand()%easyRoads.size();
            if(easyRoads[r].in==gate)good=true;
        }
        gate=easyRoads[r].out;
        return easyRoads[r].road;
    }else if(diff == 2){
        while(!good){
            r = rand()%normalRoads.size();
            if(normalRoads[r].in==gate)good=true;
        }
        gate=normalRoads[r].out;
        return normalRoads[r].road;
    }else{
        roadSample idS;
        return idS.road;
    }
}
