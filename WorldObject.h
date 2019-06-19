//
// Created by alex on 18/06/19.
//

#include "vector2.h"
#include <string>
#include <cstring>

#define MAP_SIZE_X 100
#define MAP_SIZE_Y 100


#ifndef PRACTICE_WORLDOBJECT_H
#define PRACTICE_WORLDOBJECT_H

using namespace std;

class WorldObject { //object that appears in the map. May be Person or an inanimate object

protected:
    vector2 pos;
    const char *symbol = "!";
    bool deleting;

public:
    WorldObject(vector2 pos) {
        this->pos = pos;
        deleting = false;
    }


    const char *getSymbol();

    const vector2 getPos();

    void setPos(vector2 v);

    const bool isDeleting();


};

#endif //PRACTICE_WORLDOBJECT_H
