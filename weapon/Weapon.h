#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>

using namespace std;

class Weapon{
    public:
        Weapon();
        int GetAmmo();
        void Fire(string shooter);
        void Reload();
    private:
        int ammo;
};

#endif