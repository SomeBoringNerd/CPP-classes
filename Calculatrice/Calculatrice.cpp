#include "Calculatrice.h"

float Calculatrice::Add(float a, float b)
{
    return a + b;
}

float Calculatrice::Rem(float a, float b)
{
    return a - b;
}

float Calculatrice::Mul(float a, float b)
{
    return a * b;
}

float Calculatrice::Div(float a, float b)
{
    if(a != 0){
        return a / b;
    }else{
        return 0;
    }
}

int Calculatrice::Mod(int a, int b)
{
    if(a != 0)
    {
        return a % b;
    }else{
        return 0;
    }
}