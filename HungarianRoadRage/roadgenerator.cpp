#include "roadgenerator.h"

// Initialize gate, read roads from "debug/roads/easyRoads.rds", "debug/roads/easyRoads.rds".
RoadGenerator::RoadGenerator()
{
    gate=1;
    readRoadFromFile("debug/roads/easyRoads.rds",1);
    readRoadFromFile("debug/roads/normalRoads.rds",2);
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
        /// TODO: Send exception.
        return;
    }

    // Start reading data
    bool idbool;
    while (!infile.eof())
    {
        roadSample roadSample;
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
        if(diff==1)
        {
            if (roadSample.in == 0)     easyRoads0.push_back(roadSample);
            else if(roadSample.in == 1) easyRoads1.push_back(roadSample);
            else if(roadSample.in == 2) easyRoads2.push_back(roadSample);
        }
        else if(diff==2)
        {
            if (roadSample.in == 0)     normalRoads0.push_back(roadSample);
            else if(roadSample.in == 1) normalRoads1.push_back(roadSample);
            else if(roadSample.in == 2) normalRoads2.push_back(roadSample);
        }
    }
    infile.close();
}

// return with the next road with the choosen difficulty
std::vector<std::vector<bool> > RoadGenerator::getRoad(const unsigned short &diff)
{
    int randInt(0);
    if(diff == 1)
    {
        if(gate == 0)
        {
            randInt = rand()%easyRoads0.size();
            gate=easyRoads0[randInt].out;
            return easyRoads0[randInt].road;
        }
        else if (gate == 1)
        {
            randInt = rand()%easyRoads1.size();
            gate=easyRoads1[randInt].out;
            return easyRoads1[randInt].road;
        }
        else
        {
            randInt = rand()%easyRoads2.size();
            gate=easyRoads2[randInt].out;
            return easyRoads2[randInt].road;
        }
    }
    else if(diff == 2)
    {
        if(gate == 0)
        {
            randInt = rand()%normalRoads0.size();
            gate=normalRoads0[randInt].out;
            return normalRoads0[randInt].road;
        }
        else if (gate == 1)
        {
            randInt = rand()%normalRoads1.size();
            gate=normalRoads1[randInt].out;
            return normalRoads1[randInt].road;
        }
        else
        {
            randInt = rand()%normalRoads2.size();
            gate=normalRoads2[randInt].out;
            return normalRoads2[randInt].road;
        }
    }
    else
    {
        roadSample idS;
        return idS.road;
    }
}
