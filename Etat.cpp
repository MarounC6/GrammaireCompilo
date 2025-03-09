#include "Etat.h"
#include "automate.h"
#include "Expr.h"

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


bool E1::transition(Automate & automate, Symbole * s) {
    switch (*s) {
        case PLUS:
            automate.decalage(s, new E4);
            break;
        case MULT:
            automate.decalage(s, new E5);
            break;
        case FIN:
            // État d'acceptation
            return false;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool E2::transition(Automate & automate, Symbole * s) {
    switch (*s) {
        case INT:
            automate.decalage(s, new E3);
            break;
        case OPENPAR:
            automate.decalage(s, new E2);
            break;
        case EXPR:
            automate.transitionSimple(s, new E6);
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool E3::transition(Automate & automate, Symbole * s) {
    Entier * s1;
    switch (*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
            s1 = (Entier*) automate.popSymbole();
            automate.reduction(5, new ExprVal(s1->getValeur()));
            delete s1;
            break;
        
            /*
            s1 = (Entier*) automate.popSymbole();
            automate.reduction(5, new ExprPlus(new ExprVal(0), new ExprVal(s1->getValeur())));
            break;
            */
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool E4::transition(Automate & automate, Symbole * s) {
    switch (*s) {
        case EXPR:
            automate.transitionSimple(s, new E7);
            break;
        case INT:
            automate.decalage(s, new E3);
            break;
        case OPENPAR:
            automate.decalage(s, new E2);
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool E5::transition(Automate & automate, Symbole * s) {
    switch (*s) {
        case EXPR:
            automate.transitionSimple(s, new E8);
            break;
        case INT:
            automate.decalage(s, new E3);
            break;
        case OPENPAR:
            automate.decalage(s, new E2);
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool E6::transition(Automate & automate, Symbole * s) {
    switch (*s) {
        case PLUS:
            automate.decalage(s, new E4);
            break;
        case MULT:
            automate.decalage(s, new E5);
            break;
        case CLOSEPAR:
            automate.decalage(s, new E9);
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool E7::transition(Automate & automate, Symbole * s) {
    Expr * s1;
    Expr * s2;
    Expr * snotused;
    
    switch (*s) {
        case CLOSEPAR:
        case FIN:
        case PLUS:
            s1 = (Expr*) automate.popSymbole();
            snotused = (Expr*) automate.popSymbole();
            delete snotused;
            s2 = (Expr*) automate.popSymbole();
            automate.reduction(2, new ExprPlus(s1, s2));
            //adding s1 and s2 to the pile_symboles_to_delete
            automate.addSymboleToDelete(s1);
            automate.addSymboleToDelete(s2);
            break;
        case MULT:
            automate.decalage(s, new E5);
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool E8::transition(Automate & automate, Symbole * s) {
    Expr * s1;
    Expr * s2;
    Expr * snotused;
    
    switch (*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
            s1 = (Expr*) automate.popSymbole();
            snotused = (Expr*) automate.popSymbole();
            delete snotused;
            s2 = (Expr*) automate.popSymbole();
            automate.reduction(3, new ExprMult(s1, s2));
            //adding s1 and s2 to the pile_symboles_to_delete
            automate.addSymboleToDelete(s1);
            automate.addSymboleToDelete(s2);
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool E9::transition(Automate & automate, Symbole * s) {
    Expr * s1;
    Expr * snotused;
    
    switch (*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
            snotused = (Expr*) automate.popSymbole();
            delete snotused;
            s1 = (Expr*) automate.popSymbole();
            snotused = (Expr*) automate.popSymbole();
            delete snotused;
            automate.reduction(4, s1);
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}
