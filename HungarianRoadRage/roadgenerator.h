#ifndef ROADGENERATOR_H
#define ROADGENERATOR_H

#include "stdlib.h"
#include <iostream>
#include <vector>
#include <fstream>

class RoadGenerator
{
    struct roadSample{
        unsigned short in;
        unsigned short out;
        std::vector<std::vector<bool> > road;
    };
    std::vector<roadSample> easyRoads;
    std::vector<roadSample> normalRoads;
    unsigned short gate;

    void readRoadFromFile(std::string fileName,int diff);

public:
    RoadGenerator();
    std::vector<std::vector<bool> > getRoad(unsigned short diff);
};

#endif // ROADGENERATOR_H
