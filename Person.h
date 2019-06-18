//
// Created by alex on 18/06/19.
//

#include "WorldObject.h"

#ifndef PRACTICE_PERSON_H
#define PRACTICE_PERSON_H


class Person : public WorldObject {
protected:
    string name;
    string weapon;
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

    int getAc();

    int attack(Person *p);

    int getHealth();

    int getSkill();

    void setHealth(int dif);


};


#endif //PRACTICE_PERSON_H
