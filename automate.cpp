#include "automate.h"
#include "Expr.h"
#include <iostream>

using namespace std;


Automate::Automate(Lexer* l) {
    lexer = l;
    pile_etats.push_back(new E0);
}

Automate::~Automate() {


    /*
    while (!pile_etats.empty()) {
        delete pile_etats.back();
        pile_etats.pop_back();
    }
    while (!pile_symboles.empty()) {
        delete pile_symboles.back();
        pile_symboles.pop_back();
    }
    */

    /*
    for (auto it = pile_etats.begin(); it != pile_etats.end(); it++) {
        delete *it;
    }
    for (auto it = pile_symboles.begin(); it != pile_symboles.end(); it++) {
        delete *it;
    }
    */


}

void Automate::decalage(Symbole * s, Etat * e) {
    pile_symboles.push_back(s);
    pile_etats.push_back(e);

    s->Affiche();
    cout << endl;

    lexer->Avancer();
}

void Automate::reduction(int n, Symbole * s) {
    
    if (n == 5) {
        n = 1;
    } else {
        n = 3;
    }
    
    
    for (int i = 0; i < n; i++) {
        delete pile_etats.back();
        pile_etats.pop_back();
    }

    pile_etats.back()->transition(*this, s);
}

void Automate::transitionSimple(Symbole * s, Etat * e) {
    pile_etats.push_back(e);
    pile_symboles.push_back(s);
}

void Automate::run() {
    Symbole * s = lexer->Consulter();
    while (pile_etats.back()->transition(*this, s)) {
        s = lexer->Consulter();

        cout << "Pile des états: ";
        for (auto it = pile_etats.begin(); it != pile_etats.end(); it++) {
            cout << (*it)->getName() << " ";
        }
        cout << endl;
        cout << "Pile des symboles: ";
        for (auto it = pile_symboles.begin(); it != pile_symboles.end(); it++) {
            (*it)->Affiche();
            cout << " ";
        }
        cout << endl;
        cout << "Symbole courant: ";
        s->Affiche();
        cout << endl;
        cout << "--------------------------------" << endl;
        



    }

    cout << "Analyse terminée" << endl;

    eval();

    /*
    if (*pile_symboles.back() == ERREUR) {
        cout << "Erreur de syntaxe" << endl;
    } else {
        cout << "Expression correcte" << endl;
        cout << "Valeur de l'expression: ";
        eval();
    }
    */


}

Symbole* Automate::popSymbole() {
    Symbole * s = pile_symboles.back();
    pile_symboles.pop_back();
    return s;
}


void Automate::eval() {
    Expr * s_expr = (Expr*) pile_symboles.back();
    cout << s_expr->getValeur() << endl;
}




