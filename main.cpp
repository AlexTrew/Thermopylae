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
#define SPARTAN_ARMY_SIZE 300
#define PERSIAN_ARMY_SIZE 1000
#define START_DELAY 40
#define LOG_X_OFFSET 30


using namespace std;





struct vector2
{
    int x;
    int y;
};



class WorldObject{ //object that appears in the map. May be Person or an inanimate object

protected:
    vector2 pos;
    const char* symbol = "!";
    bool deleting;

public:
    WorldObject(vector2 pos){
        this->pos = pos;
        deleting = false;
    }


    const char* getSymbol();

    vector2 getPos();
    void setPos(vector2 v);
    int move(int d);
    bool getDeleting(){
        return deleting;
    }







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
    int getAc();
    int attack(Person* p);
    int getHealth();
    int getSkill();
    void setHealth(int dif);




};









class Spartan : public Person{



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


void WorldObject::setPos(vector2 v) {
    pos = v;
}

vector2 WorldObject::getPos(){
    return pos;
}

int Person::attack(Person* p){

    if(random() % 20 > p->getSkill()) {
        if (random() % 20 > p->getAc()) {

            p->setHealth(1);
        }
    }

}

int Person::getAc(){
    return ac;
}

int Person::getHealth() {
    return health;
}

void Person::setHealth(int dif){
    health = health - dif;
}

const char* WorldObject::getSymbol() {
    return symbol;
}

int Person::getSkill() {
    return skill;
}

int Person::die(){
    alive = false;
    deleting = true;
    return 0;
}



int Person::move(int d) { //add safety checks and optimise



    vector2 current = {getPos().x, getPos().y};
    vector2 update;



    if(getPos().x+1 < MAP_SIZE_X && d == 0 && strcmp(world[getPos().x+1][getPos().y]->getSymbol(), " ")==0){ //check x+1
        update = {getPos().x+1, getPos().y};

        WorldObject* tmp = world[update.x][update.y];
        world[update.x][update.y] = this;
        world[current.x][current.y] = tmp;
        setPos(update);
        tmp->setPos(current);

    }
    else if(getPos().x-1 >=0 && d == 1 && strcmp(world[getPos().x-1][getPos().y]->getSymbol(), " ")==0){ //check x-1
        update = {getPos().x-1, getPos().y};

        WorldObject* tmp = world[update.x][update.y];
        world[update.x][update.y] = this;
        world[current.x][current.y] = tmp;
        setPos(update);
        tmp->setPos(current);

    }
    else if(getPos().y+1 < MAP_SIZE_Y && d == 2 && strcmp(world[getPos().x][getPos().y+1]->getSymbol(), " ")==0){ //check y+1
        update = {getPos().x, getPos().y+1};

        WorldObject* tmp = world[update.x][update.y];
        world[update.x][update.y] = this;
        world[current.x][current.y] = tmp;
        setPos(update);
        tmp->setPos(current);
    }
    else if(getPos().y > 0 && d == 3 &&  strcmp(world[getPos().x][getPos().y-1]->getSymbol(), " ")==0){ //check y-1
        update = {getPos().x, getPos().y-1};

        WorldObject* tmp = world[update.x][update.y];
        world[update.x][update.y] = this;
        world[current.x][current.y] = tmp;
        setPos(update);
        tmp->setPos(current);
    }
    else{
        return 0;
    }

    return 0;



}





Person* soldiers[SPARTAN_ARMY_SIZE + PERSIAN_ARMY_SIZE ];


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

    for (int y = 0; y < MAP_SIZE_Y; y++)
    {
        for (int x = 0; x < MAP_SIZE_X; x++)
        {

            if(strcmp(world[x][y]->getSymbol(), " ") == 0  && c<SPARTAN_ARMY_SIZE && world[x][y] && y>PASS_Y+1)
            {
                soldiers[c] = new Spartan(15,"Spartan","spearman",18,50,{x,y},0,true);
                world[x][y] = soldiers[c];

                c++;
            }
        }
    }

    c=0;

    for (int y = 0; y < MAP_SIZE_Y; y++) //populate the world with non human world objects
    {
        for (int x = 0; x < MAP_SIZE_X; x++)
        {

            if(strcmp(world[x][y]->getSymbol()," ") == 0  && c<PERSIAN_ARMY_SIZE && world[x][y])
            {
                soldiers[SPARTAN_ARMY_SIZE + c] = new Persian(10,"persian","spearman",3,30,{x,y},0,true);
                world[x][y] = soldiers[SPARTAN_ARMY_SIZE + c];


                c++;
            }
        }
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
    init_pair(6,COLOR_WHITE,COLOR_RED);


    int c = 0;
    bool started = false;
    int n = 0;

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

                if(world[x][y]->getDeleting() == true){

                    attron(COLOR_PAIR(6));

                    mvprintw(world[x][y]->getPos().y,world[x][y]->getPos().x,world[x][y]->getSymbol());

                    attroff(COLOR_PAIR(6));
                }
                else{

                    attron(COLOR_PAIR(c));

                    mvprintw(world[x][y]->getPos().y,world[x][y]->getPos().x,world[x][y]->getSymbol());

                    attroff(COLOR_PAIR(c));

                }



                stringstream convert;
                convert << n;
                mvprintw(0,0, convert.str().c_str());




            }

        }

        if(n<START_DELAY/2) mvprintw(0,LOG_X_OFFSET,"Persian commander: \" Throw down your weapons! \"");
        if(n>=START_DELAY/2 && n<START_DELAY) mvprintw(0,LOG_X_OFFSET, "Leonidas: \" Come and take them! \"");
        if(n>=START_DELAY) started = true;


        for(Person* soldier : soldiers) //TODO add randomness, pathfinding, and space filling
        {
            int lr = 0;

            if(soldier->getDeleting() == true) world[soldier->getPos().x][soldier->getPos().y] = new Nothing({soldier->getPos().x,soldier->getPos().y});

            if(soldier->getHealth()<=0) soldier->die();

            if(started){
                if (strcmp(soldier->getSymbol(), "i") == 0) {


                    if(soldier->getPos().x< PASS_X + (PASS_WIDTH/2)-10){
                        lr = 0;
                    }
                    else if(soldier->getPos().x>= PASS_X + (PASS_WIDTH/2)+10){
                        lr=1;
                    }
                    else{
                        lr = (random() % 3);
                    }

                    switch (random() % 5) {
                        case 0:
                            soldier->move(0);
                        case 1:
                            soldier->move(1);
                        case 2:
                            soldier->move(lr);
                        case 3:
                            soldier->move(2);
                        default:
                            soldier->move(2);
                    }

                }

                    if(strcmp(soldier->getSymbol(),"@") == 0){

                        if(strcmp((world[soldier->getPos().x+1][soldier->getPos().y]->getSymbol()), "i")==0){
                            soldier->attack(static_cast<Person*>(world[soldier->getPos().x+1][soldier->getPos().y]));



                        }
                        if(strcmp((world[soldier->getPos().x-1][soldier->getPos().y]->getSymbol()), "i")==0){
                            soldier->attack(static_cast<Person*>(world[soldier->getPos().x-1][soldier->getPos().y]));


                        }
                        if(strcmp((world[soldier->getPos().x][soldier->getPos().y+1]->getSymbol()), "i")==0){
                            soldier->attack(static_cast<Person*>(world[soldier->getPos().x][soldier->getPos().y+1]));


                        }
                        if(strcmp((world[soldier->getPos().x][soldier->getPos().y-1]->getSymbol()), "i")==0){
                            soldier->attack(static_cast<Person*>(world[soldier->getPos().x][soldier->getPos().y-1]));


                        }

                    }

                    if(strcmp(soldier->getSymbol(), "i")==0){

                        if(strcmp((world[soldier->getPos().x+1][soldier->getPos().y]->getSymbol()), "@")==0){
                            soldier->attack(static_cast<Person*>(world[soldier->getPos().x+1][soldier->getPos().y]));


                        }
                        if(strcmp((world[soldier->getPos().x-1][soldier->getPos().y]->getSymbol()), "@")==0){
                            soldier->attack(static_cast<Person*>(world[soldier->getPos().x-1][soldier->getPos().y]));


                        }
                        if(strcmp((world[soldier->getPos().x][soldier->getPos().y+1]->getSymbol()), "@")==0){
                            soldier->attack(static_cast<Person*>(world[soldier->getPos().x][soldier->getPos().y+1]));


                        }
                        if(strcmp((world[soldier->getPos().x][soldier->getPos().y-1]->getSymbol()), "@")==0){
                            soldier->attack(static_cast<Person*>(world[soldier->getPos().x][soldier->getPos().y-1]));


                        }

                    }


            }
        }
        refresh();
        n++;
        usleep(100000);

    }



    endwin();
    exit(EXIT_SUCCESS);
}