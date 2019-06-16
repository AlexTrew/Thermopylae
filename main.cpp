#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <ncurses.h>
#include <unistd.h>
#include <cstring>


#define MAP_SIZE_X 100
#define MAP_SIZE_Y 100

#define PASS_WIDTH 30
#define CLIFF_X 80
#define PASS_X 30
#define PASS_Y 28
#define WATER_X 20
#define CLIFF_WATER_X 10


using namespace std;


int spartanArmySize = 300;
int persianArmySize = 1000;

struct vector2
{
    int x;
    int y;
};



class WorldObject{ //object that appears in the map. May be Person or an inanimate object

protected:
    vector2 pos;
    const char* symbol = "!";
public:
    WorldObject(vector2 pos){
        this->pos = pos;
    }

    const char* getSymbol();

    vector2 getPos();
    void setPos(vector2 v);
    int move(int d);






};

class Nothing : public WorldObject{

public:
    Nothing(vector2 pos) : WorldObject(pos){
        this->pos = pos;
            symbol = " ";
    }


};

class Water : public WorldObject{


public:

    Water(vector2 pos) : WorldObject(pos){
        this->pos = pos;
        symbol = "~";
    }

};



WorldObject* world[MAP_SIZE_X][MAP_SIZE_Y];



class Rock : public WorldObject{
public:

    Rock(vector2 pos) : WorldObject(pos){
        this->pos = pos;
        symbol = "^";
    }





};

class Person : public WorldObject{
protected:
   string name;
   string weapon;
   int skill;
   int ac;
   int health;
   int state; //attack/defend
   bool alive;
   ;

public:
    Person(vector2 pos) : WorldObject(pos){
            this->pos = pos;
    }


    int move(int d);
    int die();
    int attack(Person* p){};
    string getName();
    int getAc(){};
    vector2 getPos(){};



};









class Spartan : public Person{

    int skill;
    string name;
    string weapon;
    int ac;


public:

    Spartan(int skill, string name, string weapon, int ac, int health, vector2 pos, int state, bool alive) : Person(pos){
        this->skill = skill;
        this->name = name;
        this->weapon = weapon;
        this->ac = ac;
        this->health=health;
        this->pos=pos;
        this->state=state;
        this->alive=alive;
        symbol = "@";
    }







};




class Persian : public Person{



public:

    Persian(int skill, string name, string weapon, int ac, int health, vector2 pos, int state, bool alive) : Person(pos){
        this->skill = skill;
        this->name = name;
        this->weapon = weapon;
        this->ac = ac;
        this->health=health;
        this->pos=pos;
        this->state=state;
        this->alive=alive;
        symbol = "i";
    }





};

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

    for (int y = 0; y < MAP_SIZE_Y; y++) //populate the world with non human world objects
    {
        for (int x = 0; x < MAP_SIZE_X; x++)
        {

            if(strcmp(world[x][y]->getSymbol()," ") == 0  && c<spartanArmySize && world[x][y] && y>PASS_Y+1)
            {
                world[x][y] = new Spartan(10,"Spartan","spearman",5,5,{x,y},0,true);
                c++;
            }
        }
    }

    c=0;

    for (int y = 0; y < MAP_SIZE_Y; y++) //populate the world with non human world objects
    {
        for (int x = 0; x < MAP_SIZE_X; x++)
        {

            if(strcmp(world[x][y]->getSymbol()," ") == 0  && c<persianArmySize && world[x][y])
            {
                world[x][y] = new Persian(10,"persian","spearman",5,5,{x,y},0,true);
                c++;
            }
        }
    }

    return 0;


}

void WorldObject::setPos(vector2 v) {
    pos = {v.x,v.y};
}

vector2 WorldObject::getPos(){
    return pos;
};

const char* WorldObject::getSymbol() {
    return symbol;
}


string Person::getName(){
    return name;
}

int WorldObject::move(int d) { //add safety checks
    if(d == 0 && world[getPos().x+1][getPos().y]->getSymbol() == " "){ //check x+1
        WorldObject* tmp = world[getPos().x][getPos().y];
        world[getPos().x+1][getPos().y] = this;
        world[getPos().x][getPos().y] = tmp;
    }
    else if(d == 1 && world[getPos().x-1][getPos().y]->getSymbol() == " "){ //check x-1
        WorldObject* tmp = world[getPos().x][getPos().y];
        world[getPos().x-1][getPos().y] = this;
        world[getPos().x][getPos().y] = tmp;
    }
    else if(d == 2 && world[getPos().x+1][getPos().y+1]->getSymbol() == " "){ //check y+1
        WorldObject* tmp = world[getPos().x][getPos().y];
        world[getPos().x][getPos().y+1] = this;
        world[getPos().x][getPos().y] = tmp;
    }
    else if(d == 3 && world[getPos().x][getPos().y-1]->getSymbol() == " "){ //check y-1
        WorldObject* tmp = world[getPos().x][getPos().y];
        world[getPos().x][getPos().y-1] = this;
        world[getPos().x][getPos().y] = tmp;
    }

    return 0;



}








int main()
{
    init();
    initscr();
    curs_set(false);
    resizeterm(MAP_SIZE_X,MAP_SIZE_Y);



    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLUE);
    init_pair(2,COLOR_BLACK,COLOR_WHITE);
    init_pair(3,COLOR_GREEN,COLOR_GREEN);
    init_pair(4,COLOR_WHITE,COLOR_GREEN);
    init_pair(5,COLOR_WHITE,COLOR_GREEN);

    int c = 0;

    while(1)
    {
        for (int y = 0; y < MAP_SIZE_Y; y++)
        {
            for (int x = 0; x < MAP_SIZE_X; x++) //print map
            {
                if(strcmp(world[x][y]->getSymbol(),"~")==0) c = 1;
                if(strcmp(world[x][y]->getSymbol(),"^")==0) c = 2;
                if(strcmp(world[x][y]->getSymbol()," ")==0) c = 3;
                if(strcmp(world[x][y]->getSymbol(),"@")==0) c = 4;
                if(strcmp(world[x][y]->getSymbol(),"i")==0) c = 5;

                attron(COLOR_PAIR(c));

                mvprintw(world[x][y]->getPos().y,world[x][y]->getPos().x,world[x][y]->getSymbol());

                attroff(COLOR_PAIR(c));
            }

        }
        refresh();
    }



    endwin();
    exit(EXIT_SUCCESS);
}