//
// Created by alex on 18/06/19.
//

#include "WorldObject.h"

#ifndef PRACTICE_ROCK_H
#define PRACTICE_ROCK_H

class Rock : public WorldObject {
public:
    Rock(vector2 pos) : WorldObject(pos) {
        this->pos = pos;
        symbol = "^";
    }
};

#endif //PRACTICE_ROCK_H
