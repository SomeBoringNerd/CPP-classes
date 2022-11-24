#include <iostream>

#include "Calculatrice.h"

using namespace std;
 
int main()
{
    bool quit = false;
    
    while(!false)
    {
        cout << "Que voulez vous faire ?"           << endl
             << "1> Additionner deux nombres"       << endl
             << "2> Soustraire deux nombres"        << endl
             << "3> Multiplier deux nombres"        << endl
             << "4> Diviser deux nombres"           << endl
             << "5> (wip) Modulaire de deux nombres"<< endl
             << "6> Quitter" << endl << "> ";
        string str;
        getline(cin, str);

        if(str == "1" || str == "2" || str == "3" || str == "4" || str == "5")
        {
            Calculatrice calc;
            string n1,n2;
            cout << "entrez deux nombres (appuyez sur entrez entre les deux)" << endl << "> ";
            getline(cin, n1);
            cout << "> ";
            getline(cin, n2);

            if(str == "1"){
                cout << n1 << " + " << n2 << " = " << calc.Add(stof(n1),stof(n2)) << endl;
            }else if(str == "2"){
                cout << n1 << " - " << n2 << " = " << calc.Rem(stof(n1),stof(n2)) << endl;
            }else if(str == "3"){   
                cout << n1 << " * " << n2 << " = " << calc.Mul(stof(n1),stof(n2)) << endl;
            }else if(str == "4"){
                cout << n1 << " / " << n2 << " = " << calc.Div(stof(n1),stof(n2)) << endl;
            }else if(str == "5"){
                cout << n1 << " % " << n2 << " = " << calc.Mod(stoi(n1),stoi(n2)) << endl;
            }

        }else
        {
            if(str == "6")
            {
                cout << "au revoir !" << endl;
            }else{
                cout << "VOUS AVEZ ENTRÉ UNE VALEUR INVALIDE ET LE PROGRAMME NE SAIT PAS COMMENT RÉPONDRE !" << endl;
            }
            return 0;
        }
    }

    return 0;
}