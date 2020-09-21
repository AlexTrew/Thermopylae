//
// Created by alex on 18/06/19.
//


#include "WorldObject.h"

#ifndef PRACTICE_NOTHING_H
#define PRACTICE_NOTHING_H

class Nothing : public WorldObject {
public:
    Nothing(vector2 pos) : WorldObject(pos) {
        this->pos = pos;
        symbol = " ";
    }
};


#endif //PRACTICE_NOTHING_H
