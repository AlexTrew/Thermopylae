//
// Created by alex on 18/06/19.
//

#include "Person.h"

#ifndef PRACTICE_SPARTAN_H
#define PRACTICE_SPARTAN_H


class Spartan : public Person {


public:

    Spartan(int skill, const char* name, string weapon, int ac, int health, vector2 pos, int state, bool alive) : Person(
            pos) {
        this->skill = skill;
        this->name = name;
        this->weapon = weapon;
        this->ac = ac;
        this->health = health;
        this->pos = pos;
        this->state = state;
        this->alive = alive;
        symbol = "@";
    }


};


#endif //PRACTICE_SPARTAN_H
