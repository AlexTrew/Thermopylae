//
// Created by alex on 18/06/19.
//

#include "WorldObject.h"
#include "Narrator.h"

#ifndef PRACTICE_PERSON_H
#define PRACTICE_PERSON_H


class Person : public WorldObject {
protected:
    const char* name;
    std::string weapon;
    int skill;
    int ac;
    int health;
    int state; //attack/defend
    bool alive;;

public:
    Person(vector2 pos) : WorldObject(pos) {
        this->pos = pos;
    }



    int move(int d, WorldObject*  w[][MAP_SIZE_Y]);

    int die();

    const int getAc();

    const void attack(Person* p);

    const int getHealth();

    const int getSkill();

    const char* getName();

    const bool isAlive();

    void setHealth(const int& dif);


};


#endif //PRACTICE_PERSON_H
