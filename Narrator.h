//
// Created by alex on 24/06/19.
//


#define PRINTABLE_LINES 6

#ifndef PRACTICE_MESSAGE_H
#define PRACTICE_MESSAGE_H

#include "Person.h"
#include <ncurses.h>
#include <iostream>
#include <queue>
#include <sstream>




using namespace std;



class Narrator{


    static int line;
    static int msgNo;


public:

    static queue<string> messages;

    static void printMsg(Person* a, Person* d, int seed);


};



#endif //PRACTICE_MESSAGE_H
