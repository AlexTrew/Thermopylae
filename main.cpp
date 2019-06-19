#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
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



#define PASS_WIDTH 30
#define CLIFF_X 80
#define PASS_X 30
#define PASS_Y 28
#define WATER_X 20
#define CLIFF_WATER_X 10
#define SPARTAN_ARMY_SIZE 300
#define PERSIAN_ARMY_SIZE 1000
#define START_DELAY 100
#define LOG_X_OFFSET 30
#define SIM_LENGTH 3000


using namespace std;



static WorldObject *world[MAP_SIZE_X][MAP_SIZE_Y];

static vector<Person *> soldiers;

int init() {

    //object creation

    //WorldObject Placement

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

    for (int y = 0; y < MAP_SIZE_Y; y++) {
        for (int x = 0; x < MAP_SIZE_X; x++) {

            if (strcmp(world[x][y]->getSymbol(), " ") == 0 && c < SPARTAN_ARMY_SIZE && world[x][y] && y > PASS_Y + 1) {
                soldiers.push_back( new Spartan(12 + random() % 6, "Spartan", "spearman", 13, 30, {x, y}, 0, true));
                world[x][y] = soldiers.at(c);

                c++;
            }
        }
    }

    c = 0;

    for (int y = 0; y < MAP_SIZE_Y; y++) //populate the world with non human world objects
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

    while (n < SIM_LENGTH) {
        for (int y = 0; y < MAP_SIZE_Y; y++) {
            for (int x = 0; x < MAP_SIZE_X; x++) //print map
            {

                if (strcmp(world[x][y]->getSymbol(), "~") == 0) c = 1;
                if (strcmp(world[x][y]->getSymbol(), "^") == 0) c = 2;
                if (strcmp(world[x][y]->getSymbol(), " ") == 0) c = 3;
                if (strcmp(world[x][y]->getSymbol(), "@") == 0) c = 4;
                if (strcmp(world[x][y]->getSymbol(), "i") == 0) c = 5;


                if (world[x][y]->isDeleting()) {

                    attron(COLOR_PAIR(6));
                    mvprintw(world[x][y]->getPos().y, world[x][y]->getPos().x, world[x][y]->getSymbol());
                    attroff(COLOR_PAIR(6));
                } else {

                    attron(COLOR_PAIR(c));
                    mvprintw(world[x][y]->getPos().y, world[x][y]->getPos().x, world[x][y]->getSymbol());
                    attroff(COLOR_PAIR(c));

                }


                stringstream convert;
                convert << n;
                mvprintw(0, 0, convert.str().c_str());


            }

        }

        if (n < START_DELAY / 2) mvprintw(0, LOG_X_OFFSET, "Persian commander: \" Throw down your weapons! \"");
        if (n >= START_DELAY / 2 && n < START_DELAY) mvprintw(0, LOG_X_OFFSET, "Leonidas: \" Come and take them! \"");
        if (n >= START_DELAY) started = true;


        int i = 0;

        for (Person *soldier : soldiers)
        {
            int lr = 0;

            if (soldier->isDeleting()){
                soldiers.at(i) = new Body();
                world[soldier->getPos().x][soldier->getPos().y] = soldiers.at(i);

            }

            if(soldier->isAlive()){
                if (soldier->getHealth() <= 0) soldier->die();

                if (started) {
                    if (strcmp(soldier->getSymbol(), "i") == 0) {


                        if (soldier->getPos().x < PASS_X + (PASS_WIDTH / 2) - 10) {
                            lr = 0;
                        } else if (soldier->getPos().x >= PASS_X + (PASS_WIDTH / 2) + 10) {
                            lr = 1;
                        } else {
                            lr = (random() % 3);
                        }

                        switch (random() % 5) {
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

                    }
//fix by using cell contents rather than WorldObject location
                    if (strcmp(soldier->getSymbol(), "@") == 0) {

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

                    if (strcmp(soldier->getSymbol(), "i") == 0) {

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
        refresh();
        n++;
        usleep(50000);

    }

    endwin();




    for (int x=0; x < MAP_SIZE_X; x++) {
        for (int y=0; y < MAP_SIZE_Y; y++)
            delete world[x][y];
    }

    cout << "program exited successfully" << endl;


    exit(EXIT_SUCCESS);
}