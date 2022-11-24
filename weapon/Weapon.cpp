#include "Weapon.h"
#include <iostream>

using namespace std;
/**
 * Constructeur, set les munitions a 6
*/
Weapon::Weapon()
{
    this->ammo = 6;
}
/**
 * Getter pour le nombre de munitions restantes
*/
int Weapon::GetAmmo()
{
    return this->ammo;
}
/**
 * set les munitions a 6
*/
void Weapon::Reload()
{
    this->ammo = 6;
}

/**
 * Gère les munitions, et print un peu de texte.
 * Appelle la fonction Reload() si besoin.
 * @param shooter : nom du tireur, passé par la classe Duelist
*/
void Weapon::Fire(string shooter)
{
    if(ammo == 0)
    {
        cout << shooter << " essaye de tirer mais son arme n'a plus de munition, il recharge." << endl;
        Reload();
    }else
    {
        ammo--;
        cout << shooter << " a tiré ! il lui reste " << GetAmmo() << "/6 munitions !" << endl;
        
    }
}