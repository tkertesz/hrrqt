#ifndef SETTINGS_H
#define SETTINGS_H

class Settings{
public:
    static const int            FREQUENCY     = 1000/40;            //A kép frissítésének időköze
    static const short          STEP_SIZE     = 6;                  //A lépésenként mozgó pixelek száma
    static const int            SCREEN_WIDTH  = 500;                //Út és a képernyő szélessége
    static const int            SCREEN_HEIGHT = 590;                //Képernyő magassága, egyenlő a graphicsview magasságával!!!
    static const int            ROAD_HEIGHT   = 600;                //Út magassága, NE változtasd!
    static const int            FIELD_WIDTH  = SCREEN_WIDTH/4.635;  //Egy mezőnek a szélessége
    static const int            FIELD_HEIGHT = FIELD_WIDTH*0.85;    //Egy mező magassága
    static const unsigned int   ROAD_SIZE  = (SCREEN_HEIGHT+ROAD_HEIGHT)/FIELD_HEIGHT;    //Hány koordináta fér el a képernyő hosszán

};

#endif // SETTINGS_H
