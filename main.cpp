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
   cout << "Tous les autres cas d'erreur de syntaxes arrêtent l'analyse, en indiquant les symboles attendus et le symbole reçu" << endl;
   cout << endl;
   cout << "Il faut noter que nous avons géré la mémoire de manière à ne pas avoir de fuites de mémoire" << endl;
   cout << "Nous faisions réguilèrement des delete sur les symboles qui ne sont plus utilisés" << endl;
   cout << "Vous pouvez essayer avec valgrind ./go pour vérifier qu'il n'y a pas de fuites de mémoire" << endl;
   cout << endl;
   cout << "Exemple d'expression valide: (1+34)*123" << endl;
   cout << "Exemple d'expression valide (avec deux symboles '+'): (1+(2+(3+(4+(5++0)))))" << endl;
   cout << "Exemple d'expression invalide (renvoie une erreur en arrêtant l'analyse): 1+*2" << endl;
   cout << "Exemple d'expression invalide (renvoie une erreur en arrêtant l'analyse): 1+(2*3" << endl;
   cout << "Exemple d'expression invalide (renvoie une erreur en arrêtant l'analyse): 1+2)" << endl;
   cout << "Exemple d'expression valide avec trois symboles '+' à la suite (Gestion de l'erreur en gardant le premier): 1+++2" << endl;
   cout << endl;


   string chaine;//("(1+34)*123)");
   char on = 'y';
   while(on=='y'){
      cout << "Veuillez rentrer une expression arithmétique: ";
      getline(cin, chaine);

      Lexer *l = new Lexer(chaine);
      Automate automate(l);

      cout << chaine <<endl;

      automate.run();
      
      cout << "Tapez 'y' pour continuer: ";
      cin >> on;
   }
  

   return 0;
}

