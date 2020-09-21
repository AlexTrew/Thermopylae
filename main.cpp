#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <ncurses.h>
#include <unistd.h>
#include <cstring>
#include <vector>

#include "WorldObject.h"
#include "Person.h"
#include "Spartan.h"
#include "Persian.h"
#include "Rock.h"
#include "Water.h"
#include "Nothing.h"
#include "Body.h"



#define PASS_WIDTH 30 //with of the hot gates
#define CLIFF_X 80 // x coordinate at which the cliff will be drawn
#define PASS_X 30 // x coordinate at which the west side of the hot gates will start
#define PASS_Y 28 //y coordinate at which the hot gates will appear
#define WATER_X 20 // x coordinate before which water will be drawn
#define CLIFF_WATER_X 10 // x coordinate at which the west cliff will begin
#define SPARTAN_ARMY_SIZE 300 // size of the spartan army
#define PERSIAN_ARMY_SIZE 1000 //size of the persian army
#define START_DELAY 130 // no. of frames of text before the simulation begins
#define LOG_X_OFFSET 30 // x coordinate of text messages
#define SIM_LENGTH 3000 // number of frames before the simulation closes
#define MSG_DISPLAY_TIME 1 //number of frames for which a message will be displayed
#define NO_OF_MESSAGES 8 // maximum number of messages to be drawn on the screen at once
#define FRAME_DELAY 100000 //time delay between each frame in nanoseconds



static WorldObject *world[MAP_SIZE_X][MAP_SIZE_Y]; //array containing object placement info
static std::vector<Person *> soldiers; //pointers to soldiers

int init() {

    for (int x = 0; x < MAP_SIZE_X; x++) //populate the world with non human world objects
    {
        for (int y = 0; y < MAP_SIZE_Y; y++) {
            if (x < WATER_X) {
                world[x][y] = new Water({x, y});
            } else if (x > CLIFF_X) {
                world[x][y] = new Rock({x, y});
            } else {
                world[x][y] = new Nothing({x, y});
            }
            if (y > PASS_Y && x > CLIFF_WATER_X && (x < PASS_X || x > PASS_X + PASS_WIDTH)) {
                world[x][y] = new Rock({x, y});
            }
        }
    }

    int c = 0;
    for (int y = 0; y < MAP_SIZE_Y; y++) { //create and populate the world with spartans
        for (int x = 0; x < MAP_SIZE_X; x++) {

            if (strcmp(world[x][y]->getSymbol(), " ") == 0 && c < SPARTAN_ARMY_SIZE && world[x][y] && y > PASS_Y + 1) {
                soldiers.push_back( new Spartan(12 + random() % 6, "Spartan", "spearman", 13, 30, {x, y}, 0, true));
                world[x][y] = soldiers.at(c);
                c++;
            }
        }
    }

    c = 0;
    for (int y = 0; y < MAP_SIZE_Y; y++) //create and populate the world with persians
    {
        for (int x = 0; x < MAP_SIZE_X; x++) {
            if (strcmp(world[x][y]->getSymbol(), " ") == 0 && c < PERSIAN_ARMY_SIZE && world[x][y]) {
                soldiers.push_back( new Persian(6 + random() % 5, "persian", "spearman", 5, 30, {x, y}, 0, true));
                world[x][y] = soldiers.at(SPARTAN_ARMY_SIZE + c);
                c++;
            }
        }
    }
    return 0;
}

int main() {
    init();
    initscr();
    curs_set(false);
    resizeterm(MAP_SIZE_X, MAP_SIZE_Y);
    //set colour pairings
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
    init_pair(4, COLOR_WHITE, COLOR_GREEN);
    init_pair(5, COLOR_BLACK, COLOR_GREEN);
    init_pair(6, COLOR_WHITE, COLOR_RED);
	
    int c = 0;
    bool started = false;
    int n = 0;
    int msgNo = 1;
    string display[NO_OF_MESSAGES]; //store messages currently being drawn on the screen
	
    while (n < SIM_LENGTH) { //main loop: to be executed per frame
        for (int y = 0; y < MAP_SIZE_Y; y++) {
            for (int x = 0; x < MAP_SIZE_X; x++) //attach a colour pairing to each character type
            {
                if (strcmp(world[x][y]->getSymbol(), "~") == 0) c = 1;
                if (strcmp(world[x][y]->getSymbol(), "^") == 0) c = 2;
                if (strcmp(world[x][y]->getSymbol(), " ") == 0) c = 3;
                if (strcmp(world[x][y]->getSymbol(), "@") == 0) c = 4;
                if (strcmp(world[x][y]->getSymbol(), "i") == 0) c = 5;
                if (world[x][y]->isDeleting()) { //change the colour of a dying soldier to a red background
                    attron(COLOR_PAIR(6));
                    mvprintw(world[x][y]->getPos().y, world[x][y]->getPos().x, world[x][y]->getSymbol());
                    attroff(COLOR_PAIR(6));
                } else { // colourise each cell on the screen with the appropriate colours
                    attron(COLOR_PAIR(c));
                    mvprintw(world[x][y]->getPos().y, world[x][y]->getPos().x, world[x][y]->getSymbol());
                    attroff(COLOR_PAIR(c));
                }
            }
        }
        if (n < START_DELAY / 3) { //show credits and messages
            mvprintw(PASS_Y-13, LOG_X_OFFSET+5, "\"ASCII Battle of Thermopylae\"" );
            mvprintw(PASS_Y-9, LOG_X_OFFSET+6, "written by Alex Trew, 2019" );
        }
        if (n < (START_DELAY / 3) * 2 && n >= START_DELAY/3 ) mvprintw(0, LOG_X_OFFSET, "Persian commander: \" Throw down your weapons! \"");
        if (n >= ( START_DELAY/3)*2 && n < START_DELAY) mvprintw(0, LOG_X_OFFSET, "Leonidas: \" Come and take them! \"");
        if (n >= START_DELAY) started = true;

        int i = 0;
        for (Person *soldier : soldiers) //solider computations loop
        {
            int lr = 0; //bias as to the direction the persians will randomly move (left/right)

            if (soldier->isDeleting()){ //replace dead soldier with a body ()
                soldiers.at(i) = new Body();
                world[soldier->getPos().x][soldier->getPos().y] = soldiers.at(i);
            }
            //kill a soldier whose health is 0
            if(soldier->isAlive()){
                if (soldier->getHealth() <= 0) soldier->die();
                //decide which direction persians move while advancing
                if (started) {
                    if (strcmp(soldier->getSymbol(), "i") == 0) {
                        if (soldier->getPos().x < PASS_X + (PASS_WIDTH / 2) - 10) {
                            lr = 0;
                        } else if (soldier->getPos().x >= PASS_X + (PASS_WIDTH / 2) + 10) {
                            lr = 1;
                        } else {
                            lr = (random() % 3);
                        }
                        switch (random() % 5) { //move soldiers with random bias
                            case 0:
                                soldier->move(0,world);
                            case 1:
                                soldier->move(1,world);
                            case 2:
                                soldier->move(lr,world);
                            case 3:
                                soldier->move(2,world);
                            default:
                                soldier->move(2,world);
                        }
                    }if (strcmp(soldier->getSymbol(), "@") == 0) { //if spartan is adjacent to enemy soldier, attack once per frame

                        if (strcmp((world[soldier->getPos().x + 1][soldier->getPos().y]->getSymbol()), "i") == 0) {
                            soldier->attack(static_cast<Person *>(world[soldier->getPos().x + 1][soldier->getPos().y]));
                        }
                        if (strcmp((world[soldier->getPos().x - 1][soldier->getPos().y]->getSymbol()), "i") == 0) {
                            soldier->attack(static_cast<Person *>(world[soldier->getPos().x - 1][soldier->getPos().y]));
                        }
                        if (strcmp((world[soldier->getPos().x][soldier->getPos().y + 1]->getSymbol()), "i") == 0) {
                            soldier->attack(static_cast<Person *>(world[soldier->getPos().x][soldier->getPos().y + 1]));
                        }
                        if (strcmp((world[soldier->getPos().x][soldier->getPos().y - 1]->getSymbol()), "i") == 0) {
                            soldier->attack(static_cast<Person *>(world[soldier->getPos().x][soldier->getPos().y - 1]));
                        }

                    }
                    if (strcmp(soldier->getSymbol(), "i") == 0) { //if persian is adjacent to enemy soldier, attack once per frame

                        if (strcmp((world[soldier->getPos().x + 1][soldier->getPos().y]->getSymbol()), "@") == 0) {
                            soldier->attack(static_cast<Person *>(world[soldier->getPos().x + 1][soldier->getPos().y]));
                        }
                        if (strcmp((world[soldier->getPos().x - 1][soldier->getPos().y]->getSymbol()), "@") == 0) {
                            soldier->attack(static_cast<Person *>(world[soldier->getPos().x - 1][soldier->getPos().y]));
                        }
                        if (strcmp((world[soldier->getPos().x][soldier->getPos().y + 1]->getSymbol()), "@") == 0) {
                            soldier->attack(static_cast<Person *>(world[soldier->getPos().x][soldier->getPos().y + 1]));
                        }
                        if (strcmp((world[soldier->getPos().x][soldier->getPos().y - 1]->getSymbol()), "@") == 0) {
                            soldier->attack(static_cast<Person *>(world[soldier->getPos().x][soldier->getPos().y - 1]));
                        }
                    }
                }
            }
            i++;
        }

        //Narration
        //pop the front of the message queue and add to the display array
        if(!Narrator::messages.empty() && n % MSG_DISPLAY_TIME == 0){
            display[msgNo % NO_OF_MESSAGES] = Narrator::messages.front();
            ++msgNo;
            Narrator::messages.pop();
        }

        //display messages in the display array
        unsigned int j = NO_OF_MESSAGES - 1;
        for(string& message : display){
            mvprintw( j % NO_OF_MESSAGES,LOG_X_OFFSET,message.c_str());
            j++;
        }
        //refresh the screen once per frame
        refresh();
        n++;
        usleep(FRAME_DELAY);
    }
    endwin();
	
    //cleanup
    for (int x=0; x < MAP_SIZE_X; x++) {
        for (int y=0; y < MAP_SIZE_Y; y++)
            delete world[x][y];
    }
    cout << "program exited successfully" << endl;
    exit(EXIT_SUCCESS);
}