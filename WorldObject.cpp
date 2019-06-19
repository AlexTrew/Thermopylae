//
// Created by alex on 18/06/19.
//

#include "WorldObject.h"


void WorldObject::setPos(const vector2& v) {
    pos = v;
}

const vector2 WorldObject::getPos() {
    return pos;
}

const char *WorldObject::getSymbol() {
    return symbol;
}

const bool  WorldObject::isDeleting() {
    return deleting;
}
