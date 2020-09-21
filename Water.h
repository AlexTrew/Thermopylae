//
// Created by alex on 18/06/19.
//


#include "WorldObject.h"

#ifndef PRACTICE_WATER_H
#define PRACTICE_WATER_H

class Water : public WorldObject {

public:

    Water(vector2 pos) : WorldObject(pos) {
        this->pos = pos;
        symbol = "~";
    }
};

#endif //PRACTICE_WATER_H
