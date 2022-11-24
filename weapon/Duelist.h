#ifndef DUELIST_H
#define DUELIST_H

#include "Weapon.h"
#include <iostream>

using namespace std;

class Duelist
{
    public:
        Duelist(string name);
        string getName();
        void itsTime();

        Weapon weapon;
    private:
        string name;

};

#endif