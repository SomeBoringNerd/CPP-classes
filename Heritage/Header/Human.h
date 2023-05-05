#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>

using namespace std;

class Human{
    public:
        Human(string, int);
        void Manger();

        string getName();
        int getAge();
    private:
        int age;
        string name;
};

class Prof : Human
{
    public:
        Prof(string, int);
        string getClasseName();
    private:
        int salaire;
};

class Student : Human
{
    public:
        Student(string, int);
        string getClasseName();
    private:
        int Moyenne;
};

#endif