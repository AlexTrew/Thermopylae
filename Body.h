//
// Created by alex on 18/06/19.
//

#include "Person.h"

#ifndef PRACTICE_BODY_H
#define PRACTICE_BODY_H

class Body : public Person{
public:
    Body() : Person(pos){
        this->symbol = " ";
        this->alive = false;
    };
};

#endif //PRACTICE_BODY_H
