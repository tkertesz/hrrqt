#ifndef SETTINGS_H
#define SETTINGS_H

class Settings{
public:
    static const int            ROAD_WIDTH = 600;               //Út és a képernyő szélessége
    static const int            ROAD_HEIGHT = 942;              //Út magassága
    static const int            SCREEN_HEIGHT = 700;            //Képernyő magassága
    static const int            CAR_WIDTH = ROAD_WIDTH/4.635;   //Az autó szélessége
    static const int            CAR_HEIGHT = CAR_WIDTH*1.7;     //Az autó magassága
    static const unsigned int   ROAD_SIZE = (int) SCREEN_HEIGHT/CAR_HEIGHT;    //Hány koordináta fér el a képernyő hosszán
};

#endif // SETTINGS_H
