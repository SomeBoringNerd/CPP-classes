#include <iostream>
#include <sqlite3.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>

using namespace std;

sqlite3 *db;

bool mustExecute, canLog;

string name;
string password;
int balance;

/**
 * @brief vérifie si un fichier existe
 * @param name nom du fichier
 * @return si le fichier existe
*/
bool fileExist(string name)
{
    ifstream f(name.c_str());
    return f.good();
}

/**
 * @brief wrapper pour std afin de faire un petit texte stylé
 * @param texte texte a printer
*/
void print(string texte)
{
    cout << "[MBCC] > " << texte.c_str() << endl;
}

/**
 * @brief même chose que print mais sans le texte fancy
 * @param texte texte a printer
*/
void printNoFancy(string texte)
{
    cout << texte.c_str() << endl;
}
/**
 * permet de init des valeurs lors de la connexion
*/
int callback(void *data, int argc, char **argv, char **azColName)
{
    for(int i = 0; i < argc; i++)
    {
        string col = azColName[i];

        if(col == "BALANCE")
        {
            string balance_str = argv[i];
            balance = stoi(balance_str);
        }
        else if(col == "NAME")
        {
            string _name = argv[i];

            name = _name;
        }else if(col == "PASSWORD"){
            if(password == argv[i]){
                canLog = true;
            }
        }
    }

    return 0;
}

void UpdateLogged()
{
    bool logged = true;

    while(logged)
    {
        printNoFancy("Bienvenue a la MegaBancc, " + name + ", veuillez selectionner une option : ");
        printNoFancy("[1] : Consulter compte");
        printNoFancy("[2] : Retirer de l'argent");
        printNoFancy("[3] : Changer votre mot de passe");
        printNoFancy("[5] : Se deconnecter");

        string str;
        getline(cin, str);

        switch(stoi(str))
        {
            case 1:{
                cout << "[MBCC] > vous avez " << balance << "€ sur votre compte" << endl;
                break;}
            case 2:{
                cout << "entrez la somme a retirer de votre compte" << endl;
                string somme;
                getline(cin, somme);

                if(stoi(somme) > balance){
                    cout << "vous n'avez pas assez d'argent pour retirer une telle somme" << endl;
                }else{
                    balance -= stoi(somme);
                    // @todo : fixer ça
                    system("/usr/bin/eject");
                    cout << "La somme a été retirée, regardez la sortie" << endl;
                }

                string updateSomme = "UPDATE CLIENT set BALANCE=" + to_string(balance) + " WHERE NAME=\"" + name + "\";";
                
                char *updateFeedback;
                int rc = sqlite3_exec(db, updateSomme.c_str(), 0, 0, &updateFeedback);

                if(rc == SQLITE_OK)
                {
                    print("votre solde a été actualisé");
                }
                break;}
            case 3:{

                print("entrez votre mot de passe");
                string o_ps;
                getline(cin, o_ps);

                print("entrez votre nouveau mot de passe");
                string n_ps;
                getline(cin, n_ps);

                print("confirmez votre nouveau mot de passe");
                string _n_ps;
                getline(cin, _n_ps);

                if(o_ps == password && n_ps == _n_ps)
                {
                    string updateSomme = "UPDATE CLIENT set PASSWORD=" + n_ps + " WHERE NAME=\"" + name + "\";";
                    password = n_ps;
                    char *updateFeedback;
                    int rc = sqlite3_exec(db, updateSomme.c_str(), 0, 0, &updateFeedback);

                    if(rc == SQLITE_OK)
                    {
                        print("votre mot de passe a été actualisé");
                    }
                }

                break;
            }
            case 4:
            {   

                print("entrez votre mot de passe");
                string o_ps;
                getline(cin, o_ps);

                if(o_ps == password)
                {
                    string updateSomme = "DELETE * FROM CLIENT WHERE NAME=\"" + name + "\";";
                
                    char *updateFeedback;
                    int rc = sqlite3_exec(db, updateSomme.c_str(), 0, 0, &updateFeedback);

                    if(rc == SQLITE_OK)
                    {
                        print("votre compte a été supprimé, adieu.");
                    }
                }

                logged = false;
                canLog = false;
                break;
            }
            case 5:{
                logged = false;
                canLog = false;
                break;
            }
        }
    }
}

/**
 * @brief mainloop
*/
void loop()
{
    while(mustExecute)
    {
        printNoFancy("Bienvenue a la MegaBancc, veuillez selectionner une option : ");
        printNoFancy("[1] : Se connecter");
        printNoFancy("[2] : Créer un compte");
        printNoFancy("[3] : Fermer le programme");
        string str;
        getline(cin, str);

        if(str == "1")
        {
            printNoFancy("Entrez votre nom d'utilisateur : ");
            string user;
            getline(cin, user);

            printNoFancy("Entrez votre mot de passe : ");
            
            getline(cin, password);

            string request = "SELECT * FROM CLIENT WHERE NAME =\"" + user + "\";";
            char *feedback_login;
            char* data;

            if(sqlite3_exec(db, request.c_str(), callback, 0, &feedback_login) == SQLITE_OK)
            {
                // boucle nestée, whoah ça fait peur
                // blague a part, y'a assez de code spaggethi dans cette fonction
                if(canLog){
                    UpdateLogged();
                    print("Connecté");
                }else{
                    print("Mauvais mot de passe");
                }
            }
            else
            {
                fprintf(stderr, "%s", feedback_login);
                print("erreur");
            }
        }
        else if(str == "2")
        {
            printNoFancy("Entrez votre nom d'utilisateur : ");
            string user;
            getline(cin, user);

            printNoFancy("Entrez votre mot de passe : ");
            string password;
            getline(cin, password);

            printNoFancy("Confirmez votre mot de passe : ");
            string _password;
            getline(cin, _password);

            string request = "SELECT * FROM CLIENT WHERE NAME =\"" + user + "\";";
            char *feedback_reg;
            if(password == _password)
            {
                if(sqlite3_exec(db, request.c_str(), 0, 0, &feedback_reg))
                {
                    print("Un compte avec ce nom existe déjà");
                }else
                {
                    string _request = "INSERT INTO CLIENT VALUES(\"" + user + "\", 20, \"" + password + "\");";

                    char *feedback_reg2;

                    if(sqlite3_exec(db, _request.c_str(), 0, 0, &feedback_reg2) == SQLITE_OK)
                    {   
                        print("Votre compte a été créé avec succès");
                    }else{
                        print("Une erreur est survenue");
                    }
                }
            }else{
                print("La verification du mot de passe a echoué, faites attention a bien écrire deux fois le même mot de passe.");
            }
        }
        else if(str == "3")
        {
            print("Au Revoir !");
            mustExecute = false;
        }else 
        {
            print("Mauvaise option selectionnée");
        }
    }
}
 
int main()
{
    
    // check si le fichier de la base de donnée existe
    // a faire avant sqlite3_open car le fichier sera créé dans tout les cas
    bool markForCreation = !fileExist("Banque_Test");

    // ouvre la db
    int rc;
    rc = sqlite3_open("Banque_Test", &db);

    // info de debug
    print("Etat de la banque :");

    // si la base de donnée existe, on passe a la loop tout de suite
    if(!markForCreation)
    {
        print("fait");
        mustExecute = true; 
        loop();
    }
    // sinon on va l'initialiser
    else
    {
        print("a faire");
        
        print("Base de donnée innexistante, création des valeurs de base");

        // request
        string sql = "CREATE TABLE CLIENT (NAME TEXT NOT NULL, BALANCE INT NOT NULL, PASSWORD TEXT NOT NULL);";
        char* feedback;

        // execute la request a la recherche d'erreur
        if(sqlite3_exec(db, sql.c_str(), 0, 0, &feedback) == SQLITE_OK)
        {
            print("Base de donnée créée");

            mustExecute = true; 
            loop();
        }else
        {
            string str_feedback = feedback;

            // ça arrive que parfois, la base de donnée soit considérée comme innexistante.
            // ce "bug" n'empêche pas de lancer le programme normalement.
            if(!str_feedback.find("table CLIENT"))
            {
                print("La base de donnée n'a pas pu être créée, message d'erreur : ");
                print(feedback);
            }
            else
            {
                print("La base de donnée a été marquée comme incomplète mais celle-ci existait déjà, ce qui fait que la table CLIENT est déjà initiée et fait donc échouer le code de création de la table. Cette erreur n'empêche pas le programme de marcher comme prévu et sera donc ignorée");
                print(feedback);
                mustExecute = true; 
                loop();
            }
        }
    }

    return 0;
}