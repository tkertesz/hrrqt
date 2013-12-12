#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
public:
    static const int            STARTLIFE     = 3;                  // Number of starting life.
    static const int            FREQUENCY     = 1000/40;            // Refresh intervall of the picture.
    static const short          STEP_SIZE     = 4;                  // Number of pixels wich shifting on one move
    static const int            SCREEN_WIDTH  = 545;                // Width of the screen.
    static const int            SCREEN_HEIGHT = 590;                // Height of the screen.
    static const int            ROAD_HEIGHT   = 600;                // Height of the road. DO NOT CHANGE!
    static const int            FIELD_WIDTH  = SCREEN_WIDTH/4.635;  // Width of one field. DO NOT CHANGE!
    static const int            FIELD_HEIGHT = SCREEN_WIDTH/5.453;  // Height of one field. DO NOT CHANGE!
                                                                    //Number of fields in one road.
    static const unsigned int   ROAD_SIZE  = (SCREEN_HEIGHT+ROAD_HEIGHT)/FIELD_HEIGHT;
};

#endif // SETTINGS_H
