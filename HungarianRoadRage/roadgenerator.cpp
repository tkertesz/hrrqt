#include "roadgenerator.h"

// Initialize gate, read roads from "debug/roads/easyRoads.rds", "debug/roads/easyRoads.rds".
RoadGenerator::RoadGenerator()
{
    gate=1;
    readRoadFromFile("debug/roads/beginnerRoads.rds",1);
    readRoadFromFile("debug/roads/easyRoads.rds",2);
    readRoadFromFile("debug/roads/normalRoads.rds",3);
}

// Read road from file
void RoadGenerator::readRoadFromFile(const std::string &fileName, const int &diff)
{

    // Create streamobject
    std::ifstream infile;
    infile.open(fileName);

    // Exit if file opening failed
    if (!infile.is_open())
    {
        return;
    }

    // Start reading data
    bool idbool;
    std::vector<RoadSample> roads0;
    std::vector<RoadSample> roads1;
    std::vector<RoadSample> roads2;
    while (!infile.eof())
    {
        RoadSample roadSample;
        infile >> roadSample.in >> roadSample.out;
        for(int i=0; i<6; i++)
        {
            std::vector<bool> idVec;
            for(int j=0; j<3; j++)
            {
                infile >> idbool;
                idVec.push_back(idbool);
            }
            roadSample.road.push_back(idVec);
        }
        if (roadSample.in == 0)     roads0.push_back(roadSample);
        else if(roadSample.in == 1) roads1.push_back(roadSample);
        else if(roadSample.in == 2) roads2.push_back(roadSample);
    }
    if(diff == 1)
    {
        beginnerRoads.push_back(roads0);
        beginnerRoads.push_back(roads1);
        beginnerRoads.push_back(roads2);
    }
    else if(diff==2)
    {
        easyRoads.push_back(roads0);
        easyRoads.push_back(roads1);
        easyRoads.push_back(roads2);
    }
    else if(diff==3)
    {
        normalRoads.push_back(roads0);
        normalRoads.push_back(roads1);
        normalRoads.push_back(roads2);
    }
    infile.close();
}

// return with the next road with the choosen difficulty
std::vector<std::vector<bool> > RoadGenerator::getRoad(const unsigned short &diff)
{
    int randInt(0);
    int gateHolder;
    if(diff == 1)
    {
        gateHolder = gate;
        randInt = rand()%beginnerRoads.at(gateHolder).size();
        gate = beginnerRoads.at(gateHolder).at(randInt).out;
        return beginnerRoads.at(gateHolder).at(randInt).road;
    }
    else if(diff == 2)
    {
        gateHolder = gate;
        randInt = rand()%easyRoads.at(gateHolder).size();
        gate = easyRoads.at(gateHolder).at(randInt).out;
        return easyRoads.at(gateHolder).at(randInt).road;
    }
    else if(diff == 3)
    {
        gateHolder = gate;
        randInt = rand()%normalRoads.at(gateHolder).size();
        gate = normalRoads.at(gateHolder).at(randInt).out;
        return normalRoads.at(gateHolder).at(randInt).road;
    }
    else
    {
        RoadSample idRoad;
        return idRoad.road;
    }
}
