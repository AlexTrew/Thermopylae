#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <typeinfo>


#define MAP_SIZE_X 4000
#define MAP_SIZE_Y 4000

#define PASS_WIDTH 60
#define CLIFF_X 1500
#define PASS_Y 2000
#define WATER_X 1000


using namespace std;


int spartanArmySize = 300;
int persianArmySize = 1000;

struct vector2
{
    int x;
    int y;
};



class WorldObject{ //object that appears in the map. May be person or an inanimate object

public:
    WorldObject(){

    }

    virtual string getSymbol(){

    };






};

class Nothing : public WorldObject{
public:
    string symbol = " ";
    Nothing(){

    }

    string getSymbol();
};

class Water : public WorldObject{
public:
    string symbol = "~";
    Water(){

    }
    string getSymbol();
};



WorldObject* world[MAP_SIZE_X][MAP_SIZE_Y];



class Rock : public WorldObject{

    string symbol = "\u25A0";
public:
    Rock(){

    }
    string getSymbol();



};

class person : public WorldObject{


   string name;
   int skill;
   int ac;
   int health;
   int state; //attack/defend
   bool alive;

public:
    person(){

    }
    int move(int d);
    int check(int d);
    int die();
    int attack(person p);
    int checkadj();
    virtual string getname();
    virtual string getSymbol(){};


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
    string symbol = "@";

public:

    spartan(int skill, string name, string weapon, int ac, int health, vector2 pos, int state, bool alive){
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
    int attack(person p);

    string getname();
    string getSymbol();




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
    string symbol = "i";

public:

    persian(int skill, string name, string weapon, int ac, int health, vector2 pos, int state, bool alive)
    {
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
    string getSymbol();


};

int init()
{

    //object creation
    spartan* spartans[spartanArmySize];
    persian* persians[persianArmySize];
    for(int s=0; s<spartanArmySize; s++)
    {
        ostringstream s_name;
        s_name << "spartan soldier " << s << " ";
        string name = s_name.str();

         spartans[s] = new spartan(10, name, "hoplite", 10, 5, {0,s}, 0, true);
       //  cout << spartans[s]->getname() << "reporting for duty!" << endl;
    }


    for(int p=0; p<persianArmySize; p++)
    {
        persians[p] = new persian(2, "persian soldier", "spearman", 3, 3, {1,p}, 0, true);
    }

    //WorldObject Placement

    for (int x = 0; x < MAP_SIZE_X; x++) //populate the world with non human world objects
    {
        for (int y = 0; y < MAP_SIZE_Y; y++)
        {
            if(x<WATER_X)
            {
                world[x][y] = new Water();
            }
            else if(x<CLIFF_X)
            {
                world[x][y] = new Rock();
            }

            else
            {
                world[x][y] = new Nothing();
            }
        }
    }


    for(spartan* s : spartans) //place the spartan army
    {
        world[s->getPos().x][s->getPos().y] = s;
    }

    for(persian* p : persians) //place the persian army
    {
        world[p->getPos().x][p->getPos().y] = p;
    }


    for (int x = 0; x < MAP_SIZE_X; x++) //print map
    {
        for (int y = 0; y < MAP_SIZE_Y; y++)
        {

           cout << world[x][y]->getSymbol() << " ";
        }
   }



}

string Nothing::getSymbol(){
    return symbol;
}

string Rock::getSymbol(){
    return symbol;
}

string Water::getSymbol(){
    return symbol;
}

string person::getname(){
    return name;
}


string spartan::getname(){
    return name;
}

vector2 spartan::getPos(){
    return pos;
}

string spartan::getSymbol() {
    return symbol;
}

int spartan::check(int d) {

}

int spartan::move(int d) { //add safety checks
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
        return 1;
    }
    else if(d == 3 && world[getPos().x][getPos().y-1]->getSymbol() == " "){ //check y-1
        WorldObject* tmp = world[getPos().x][getPos().y];
        world[getPos().x][getPos().y-1] = this;
        world[getPos().x][getPos().y] = tmp;
        return 1;
    }
    else{
        return 0;
    }
    return 0;
}

vector2 persian::getPos() {
    return pos;
}

string persian::getSymbol() {
    return symbol;
}





int main()
{
    init();
}