#ifndef ROADGENERATOR_H
#define ROADGENERATOR_H

#include "stdlib.h"
#include <fstream>
#include <vector>

///Author: bendaf
class RoadGenerator
{
    struct roadSample
    {
        unsigned short in;                      // The entrace coord of the road.
        unsigned short out;                     // The exit coord of the road.
        std::vector<std::vector<bool> > road;   // The vector of the road coords.
    };

    // Road vectors by difficulty and entrace.
    std::vector<roadSample> easyRoads0;
    std::vector<roadSample> easyRoads1;
    std::vector<roadSample> easyRoads2;
    std::vector<roadSample> normalRoads0;
    std::vector<roadSample> normalRoads1;
    std::vector<roadSample> normalRoads2;

    unsigned short gate;                        // The exit coord of the last generated road.
                                                // Read the road vectors from file.
    void readRoadFromFile(const std::string& fileName, const int& diff);

public:
    RoadGenerator();                            // Initialize variables.
                                                // Get the next road.
    std::vector<std::vector<bool> > getRoad(const unsigned short& diff);
};

#endif // ROADGENERATOR_H
