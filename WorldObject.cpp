//
// Created by alex on 18/06/19.
//

#include "WorldObject.h"


void WorldObject::setPos(vector2 v) {
    pos = v;
}

vector2 WorldObject::getPos() {
    return pos;
}

const char *WorldObject::getSymbol() {
    return symbol;
}
