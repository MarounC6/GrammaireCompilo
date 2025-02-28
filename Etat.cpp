#include "Etat.h"
#include "automate.h"
#include "symbole.h"

#include <iostream>


bool E0::transition(Automate & automate, Symbole * s) {
    switch (*s)
    {
        case EXPR:   
            automate.transitionSimple(s, new E1);
            break;
        case OPENPAR:
            automate.decalage(s, new E2);
            break;
        case INT:
            automate.decalage(s,new E3);
            break;
        default:
            automate.decalage(new Symbole(ERREUR),NULL);  // Mettre un etat erreur potentiellement
            return false;
            break;
    }

    return true;
}


