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
#define PASS_Y 27
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



class WorldObject{ //object that appears in the map. May be person or an inanimate object

    vector2 pos;
public:
    WorldObject(vector2 pos){
        this->pos = pos;
    }

    virtual const char* getSymbol(){

    };

    virtual vector2 getPos(){};
    virtual void setPos(vector2 v);






};

class Nothing : public WorldObject{
    vector2 pos;

public:
    const char* symbol = " ";
    Nothing(vector2 pos) : WorldObject(pos){
        this->pos = pos;
    }

    const char* getSymbol();
    vector2 getPos();
    void setPos(vector2 v);

};

class Water : public WorldObject{
    vector2 pos;

public:
    const char* symbol = "~";

    Water(vector2 pos) : WorldObject(pos){
        this->pos = pos;
    }
    const char* getSymbol();
    vector2 getPos();
    void setPos(vector2 v);

};



WorldObject* world[MAP_SIZE_X][MAP_SIZE_Y];



class Rock : public WorldObject{
    vector2 pos;
    const char* symbol = "M";
public:

    Rock(vector2 pos) : WorldObject(pos){
        this->pos = pos;
    }
    const char* getSymbol();
    vector2 getPos();
    void setPos(vector2 v);




};

class person : public WorldObject{

    vector2 pos;
   string name;
   int skill;
   int ac;
   int health;
   int state; //attack/defend
   bool alive;

public:
    person(vector2 pos) : WorldObject(pos){
            this->pos = pos;
    }

    int move(int d);
    int check(int d);
    int die();
    virtual int attack(person* p){};
    virtual string getName();
    virtual int getAc(){};
    virtual const char* getSymbol(){};
    virtual vector2 getPos(){};


};









class spartan : public person{

    int skill;
    string name;
    string weapon;
    int ac;
    int health;
    vector2 pos;
    int state; //attack/defend
    bool alive;
    const char* symbol = "@";

public:

    spartan(int skill, string name, string weapon, int ac, int health, vector2 pos, int state, bool alive) : person(pos){
        this->skill = skill;
        this->name = name;
        this->weapon = weapon;
        this->ac = ac;
        this->health=health;
        this->pos=pos;
        this->state=state;
        this->alive=alive;
    }

    int move(int d);
    int check(int d);
    vector2 getPos();
    int die();
    int checkadj();

    int attack(person* p);

    string getName();
    const char* getSymbol();
    int getAc();





};




class persian : public person{

    int skill;
    string name;
    string weapon;
    int ac;
    int health;
    vector2 pos;
    int state; //attack/defend
    bool alive;
    const char* symbol = "i";

public:

    persian(int skill, string name, string weapon, int ac, int health, vector2 pos, int state, bool alive) : person(pos){
        this->skill = skill;
        this->name = name;
        this->weapon = weapon;
        this->ac = ac;
        this->health=health;
        this->pos=pos;
        this->state=state;
        this->alive=alive;
    }
    int move(int d);
    int check(int d);
    int die();
    vector2 getPos();
    int attack(person p);
    int checkadj();
    const char* getSymbol();



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

            if(strcmp(world[x][y]->getSymbol()," ") == 0  && c<spartanArmySize && world[x][y] && y>PASS_Y)
            {
                world[x][y] = new spartan(10,"Spartan","spearman",5,5,{x,y},0,true);
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
                world[x][y] = new persian(10,"persian","spearman",5,5,{x,y},0,true);
                c++;
            }
        }
    }


/*
    for(spartan* s : spartans) //place the spartan army
    {
        world[s->getPos().x][s->getPos().y] = s;
    }

    for(persian* p : persians) //place the persian army
    {
        world[p->getPos().x][p->getPos().y] = p;
    }

*/




}

void WorldObject::setPos(vector2 v) {
    pos = {v.x,v.y};
}

void Nothing::setPos(vector2 v) {
    WorldObject::setPos(v);
}

const char* Nothing::getSymbol(){
    return symbol;
}

vector2 Nothing::getPos(){
    return pos;
}

const char* Rock::getSymbol(){
    return symbol;
}

vector2 Rock::getPos(){
    return pos;
}

void Rock::setPos(vector2 v) {
    WorldObject::setPos(v);
}


const char* Water::getSymbol(){
    return symbol;
}

vector2 Water::getPos(){
    return pos;
}

void Water::setPos(vector2 v) {
    WorldObject::setPos(v);
}

string person::getName(){
    return name;
}

int person::move(int d) { //add safety checks
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


string spartan::getName(){
    return name;
}

vector2 spartan::getPos(){
    return pos;
}

const char* spartan::getSymbol() {
    return symbol;
}

int spartan::getAc() {
    return ac;
}




int spartan::attack(person* p){
    p->getAc();

}

vector2 persian::getPos() {
    return pos;
}

const char* persian::getSymbol() {
    return symbol;
}





int main()
{
    init();
    initscr();
    resizeterm(MAP_SIZE_X,MAP_SIZE_Y);



    start_color();
    init_pair('~', COLOR_CYAN, COLOR_BLUE);


    while(1)
    {
        for (int y = 0; y < MAP_SIZE_Y; y++)
        {
            for (int x = 0; x < MAP_SIZE_X; x++) //print map
            {

                mvprintw(world[x][y]->getPos().y,world[x][y]->getPos().x,world[x][y]->getSymbol());

            }

        }
        refresh();
    }



    curs_set(false);
    sleep(10);
    endwin();
    exit(EXIT_SUCCESS);
}