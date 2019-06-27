//
// Created by alex on 24/06/19.
//

#include "Narrator.h"
#include <cstring>




queue<string> Narrator::messages;




void Narrator::printMsg(Person* a, Person* d, int seed) {

    stringstream str;






    switch(seed){
        case 0:

            str << d->getName() << " was skewered by " << a->getName() << " ";
            messages.push(str.str());
            str.str(std::string());


        case 1:
            str << d->getName() << " was stabbed in the chest by " << a->getName() << " ";
            messages.push(str.str());
            str.str(std::string());




        case 2:

            str << d->getName() << " had his head caved in by " << a->getName() << " ";
            messages.push(str.str());
            str.str(std::string());


        case 3:

            str <<  a->getName() << " hacked " << d->getName() <<" to death with a shortsword " << " ";
            messages.push(str.str());
            str.str(std::string());



        case 4:

            str << d->getName() << " was struck by a missile thrown by " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 5:
            str << d->getName() << " was executed by " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 6:
            str << d->getName() << " was stabbed in the shoulder by " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 7:

            str << d->getName() << " was choked out by " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 8:

            str << d->getName() << " had the side of his neck cut open by " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 9:

            str << d->getName() << " got speared in the stomach by " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());



        case 10:

            str << a->getName() << " beat " << d->getName() << " to death with a helmet" << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 11:

            str << d->getName() << " had his femoral artery ruptured by " << a->getName() <<"'s sword "  << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 12:

            str << a->getName() << " bashed " << d->getName() << " to death with a shield" << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 13:

            str << a->getName() << " bashed " << d->getName() << " to death with a rock" << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 14:

            str << d->getName() << " took " << a->getName() << "'s spear to the head" << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 15:
            str << a->getName() << " impaled " << d->getName() << " with his spear" << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 16:
            str << d->getName() << "'s life was tragically cut short by " << d->getName() << "'s sword" << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 17:
            str << d->getName() << "'s missile connected with " << d->getName() << ", wounding him mortally" << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 18:

            str << d->getName() << " experienced the pointy end of  " << a->getName() << "'s shortsword" << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 19:

            str << d->getName() << " experienced the pointy end of  " << a->getName() << "'s spear" << " ";
            messages.push(str.str().c_str());
            str.str(std::string());



        case 20:
            str << d->getName() << " was too slow for " << a->getName() << "'s spear" << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 21:

            str << d->getName() << " was killed by " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 22:

            str << d->getName() << " was eviscerated by " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 23:

            str << d->getName() << " was decimated by " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 24:

            str << d->getName() << " was crippled by " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 25:

            str << d->getName() << " was fatally wounded by " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 26:

            str << d->getName() << " was defeated by " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 27:

            str << a->getName() << " waved goodbye to  " << d->getName() << " with a sharp iron blade" << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 28:

            str << a->getName() << "'s spear tore into " << d->getName() << ", wounding him mortally" << " ";
            messages.push(str.str().c_str());
            str.str(std::string());


        case 29:

            str << a->getName() << "'s shield struck " << d->getName() << ", wounding him mortally" << " ";
            messages.push(str.str().c_str());
            str.str(std::string());



        case 30:

            str << d->getName() << " was shafted by " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());

        case 31:
            str << d->getName() << " didn't stand up well to " << a->getName() << "'s spear";
            messages.push(str.str().c_str());
            str.str(std::string());

        case 32:
            str << d->getName() << " sustained a crushing blow to the chest from " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());

        case 33:
            str << d->getName() << " sustained a crushing blow to the head from " << a->getName() << "";
            messages.push(str.str().c_str());
            str.str(std::string());

        case 34:
            str << d->getName() << " sustained a crushing blow to the arm from " << a->getName() << " ";
            messages.push(str.str().c_str());
            str.str(std::string());

    }
}
