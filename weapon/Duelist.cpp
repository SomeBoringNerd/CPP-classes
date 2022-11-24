#include "Duelist.h"

/**
 * Constructeur, attribue un nom et une nouvelle instance de <code>Weapon</code>
 * @param _name : nom du tireur
*/
Duelist::Duelist(string _name)
{
    this->name = _name;

    this->weapon = Weapon();
}

/**
 * Entre-deux entre la gameloop et l'instance de <code>Weapon</code>
 * du tireur.
*/
void Duelist::itsTime()
{
    weapon.Fire(getName());
}

/**
 * Retourne le nom du tireur
*/
string Duelist::getName()
{
    return name;
}