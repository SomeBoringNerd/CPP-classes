// headers pour le jeu
#include "Weapon.h"
#include "Duelist.h"

// headers pour l'output / rng
#include <stdlib.h>
#include <iostream>

// headers lié a la pause.
#include <chrono>
#include <thread>

using namespace std;
 
int main()
{
    // création des duelistes
    Duelist Numero1 = Duelist("sch1");
    Duelist Numero2 = Duelist("sch2");

    // finished gère l'état du jeu,
    // debug sert a voir les proba et rend le "jeu" infini
    bool finished, debug = false;

    // proba que le tir loupe
    int proba = 90;

    // a changer
    debug = true;

    while(!finished)
    {
        // reset la seed d'aléatoire
        srand (time(NULL));
        int chance = rand() % 100 + 1;

        // J1 tire
        Numero1.itsTime();

        if(!debug)
        {
            //check victoire puis sort de la boucle.
            if(chance > proba){
                cout << Numero1.getName() << " touche sa cible et gagne !" << endl;
                finished = true;
                break;
            }
        }else{
            cout << "[DEBUG] : p1 RNG : " << chance << "/100" << endl;
        }

        // pause le code pendant une seconde pour laisser la seed
        // se reset proprement
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // même chose pour le J2

        srand (time(NULL));
        chance = rand() % 100 + 1;

        Numero2.itsTime();

        if(!debug){
            if(chance > proba){
                cout << Numero2.getName() << " touche sa cible et gagne !" << endl;
                finished = true;
                break;
            }
        }else{
            cout << "[DEBUG] : p2 RNG : " << chance << "/100" << endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}