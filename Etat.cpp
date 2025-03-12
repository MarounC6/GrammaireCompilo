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
            automate.setError("Symboles attendus: EXPR, OPENPAR, INT.\nSymbole reçu: " + Etiquettes[*s]);
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
            automate.setError("Symboles attendus: PLUS, MULT, FIN.\nSymbole reçu: " + Etiquettes[*s]);
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
            automate.setError("Symboles attendus: INT, OPENPAR, EXPR.\nSymbole reçu: " + Etiquettes[*s]);
            return false;
    }
    return true;
}

bool E3::transition(Automate & automate, Symbole * s) {
    Entier * s1;
    Expr * e1;
    Expr * e2;
    switch (*s) {
        case PLUS:
        case MULT:
            s1 = (Entier*) automate.popSymbole();
            automate.reduction(5, new ExprVal(s1->getValeur()));
            delete s1;
            break;
        

        //Ici, ça fonctionne même si on met un entier seul comme expression, c'est le but de cette partie du code
        case CLOSEPAR:
        case FIN:
            s1 = (Entier*) automate.popSymbole();
            e1  = new ExprVal(0);
            e2 = new ExprVal(s1->getValeur());
            automate.reduction(5, new ExprPlus(e1, e2));
            delete s1;
            automate.addSymboleToDelete(e1);
            automate.addSymboleToDelete(e2);
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            automate.setError("Symboles attendus: PLUS, MULT, CLOSEPAR, FIN.\nSymbole reçu: " + Etiquettes[*s]);
            return false;
    }
    return true;
}

bool E4::transition(Automate & automate, Symbole * s) {
    Lexer * l;
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
        
        
        //Si on a deux plus à la suite, on ignore le second sans renvoyer d'erreur
        case PLUS:
            l = automate.getLexer();
            l->Avancer();
            delete s; //On delete le second plus de la chaîne d'entrée, il n'est pas dans la pile symboles
            break;
        
        default:
            automate.decalage(new Symbole(ERREUR), NULL);

            automate.setError("Symboles attendus: EXPR, INT, OPENPAR.\nSymbole reçu: " + Etiquettes[*s]);

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
            automate.setError("Symboles attendus: EXPR, INT, OPENPAR.\nSymbole reçu: " + Etiquettes[*s]);
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
            automate.setError("Symboles attendus: PLUS, MULT, CLOSEPAR.\nSymbole reçu: " + Etiquettes[*s]);
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
            automate.setError("Symboles attendus: CLOSEPAR, FIN, PLUS, MULT.\nSymbole reçu: " + Etiquettes[*s]);
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
            automate.setError("Symboles attendus: PLUS, MULT, CLOSEPAR, FIN.\nSymbole reçu: " + Etiquettes[*s]);
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
            automate.setError("Symboles attendus: PLUS, MULT, CLOSEPAR, FIN.\nSymbole reçu: " + Etiquettes[*s]);
            return false;
    }
    return true;
}
