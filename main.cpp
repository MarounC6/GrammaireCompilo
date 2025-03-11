#include <iostream>
#include "lexer.h"
#include "automate.h"

using namespace std; 


int main(void) {

   /*
   string chaine("(1+34)*123"); // (1+2)*4

   Lexer *l = new Lexer(chaine);
   Automate automate(l);

   cout << "Analyse de " << chaine << endl;
   automate.run();
   */

   cout << "Bienvenue dans le programme d'analyse syntaxique d'expressions arithmétiques" << endl;
   cout << "Nous avons décidé de considérer que s'il y a deux (ou plus) symboles '+', on gère l'erreur en gardant le premier (Transition de l'état 4)" << endl;
   cout << "Tous les autres cas d'erreur de syntaxes arrêtent l'analyse, en indiquant les symboles attendus et reçus" << endl;


   string chaine;//("(1+34)*123)");
   char on = 'y';
   while(on=='y'){
      cout << "Veuillez rentrer une expression arithmétique: ";
      cin >> chaine;

      Lexer *l = new Lexer(chaine);
      Automate automate(l);

      cout << chaine <<endl;

      automate.run();
      
      cout << "Tapez 'y' pour continuer: ";
      cin >> on;
   }
  

   return 0;
}

