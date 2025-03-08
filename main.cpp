#include <iostream>
#include "lexer.h"
#include "automate.h"

using namespace std; 


int main(void) {
   string chaine("(1+34)*123"); // (1+2)*4

   Lexer *l = new Lexer(chaine);
   Automate automate(l);

   cout << "Analyse de " << chaine << endl;
   automate.run();

   /*
   Symbole * s;
   while(*(s=l.Consulter())!=FIN) {
      s->Affiche();
      cout<<endl;
      l.Avancer();
   }
   */
   return 0;
}

