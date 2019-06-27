//
// Created by alex on 24/06/19.
//



#ifndef PRACTICE_MESSAGE_H
#define PRACTICE_MESSAGE_H

#include "Person.h"
#include <iostream>
#include <queue>
#include <sstream>




using namespace std;



class Narrator{

public:

    static queue<string> messages;

    static void printMsg(Person* a, Person* d, int seed);


};



#endif //PRACTICE_MESSAGE_H
