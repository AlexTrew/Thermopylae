//
// Created by alex on 18/06/19.
//

#include "Person.h"

const void Person::attack(Person*  p) {
    if (random() % 20 > p->getSkill()) {
        if (random() % 20 > p->getAc()) {
            p->setHealth(1);
            if(p->getHealth()<=0){
                Narrator::printMsg(this,p, random() % 35);
            }
        }
    }
}

const int Person::getAc() {
    return ac;
}

const int Person::getHealth() {
    return health;
}

const char* Person::getName() {
    return name;
}

void Person::setHealth(const int& dif) {
    health = health - dif;
}



const int Person::getSkill() {
    return skill;
}

int Person::die() {
    alive = false;
    deleting = true;
    return 0;
}

const bool Person::isAlive(){
    return alive;
}


int Person::move(int d,  WorldObject*  world[][MAP_SIZE_Y]) { //add safety checks and optimise
    vector2 current = {getPos().x, getPos().y};
    vector2 update;
    if (getPos().x + 1 < MAP_SIZE_X && d == 0 &&
        strcmp(world[getPos().x + 1][getPos().y]->getSymbol(), " ") == 0) { //check x+1
        update = {getPos().x + 1, getPos().y};

        WorldObject *tmp = world[update.x][update.y];
        world[update.x][update.y] = this;
        world[current.x][current.y] = tmp;
        setPos(update);
        tmp->setPos(current);

    } else if (getPos().x - 1 >= 0 && d == 1 &&
               strcmp(world[getPos().x - 1][getPos().y]->getSymbol(), " ") == 0) { //check x-1
        update = {getPos().x - 1, getPos().y};

        WorldObject *tmp = world[update.x][update.y];
        world[update.x][update.y] = this;
        world[current.x][current.y] = tmp;
        setPos(update);
        tmp->setPos(current);

    } else if (getPos().y + 1 < MAP_SIZE_Y && d == 2 &&
               strcmp(world[getPos().x][getPos().y + 1]->getSymbol(), " ") == 0) { //check y+1
        update = {getPos().x, getPos().y + 1};

        WorldObject *tmp = world[update.x][update.y];
        world[update.x][update.y] = this;
        world[current.x][current.y] = tmp;
        setPos(update);
        tmp->setPos(current);
    } else if (getPos().y > 0 && d == 3 &&
               strcmp(world[getPos().x][getPos().y - 1]->getSymbol(), " ") == 0) { //check y-1
        update = {getPos().x, getPos().y - 1};

        WorldObject *tmp = world[update.x][update.y];
        world[update.x][update.y] = this;
        world[current.x][current.y] = tmp;
        setPos(update);
        tmp->setPos(current);
    } else {
        return 0;
    }

    return 0;
}

