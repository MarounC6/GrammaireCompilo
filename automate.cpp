#include "automate.h"
#include "symbole.h"
#include "etat.h"


Automate::Automate(Lexer* l) {
    lexer = l;
    pile_etats.push_back(new Etat0());
}

Automate::~Automate() {
    /*
    for (auto it = pile_etats.begin(); it != pile_etats.end(); it++) {
        delete *it;
    }
    for (auto it = pile_symboles.begin(); it != pile_symboles.end(); it++) {
        delete *it;
    }
    */

    delete lexer;
}

Automate::decalage(Symbole * s, Etat * e) {
    pile_symboles.push_back(s);
    pile_etats.push_back(e);
    lexer->Avancer();
}

Automate::reduction(int n, Symbole * s) {
    for (int i = 0; i < n; i++) {
        delete pile_etats.back();
        pile_etats.pop_back();
    }

    pile_etats.back()->transition(*this, s);
}

Automate::transitionSimple(Symbole * s, Etat * e) {
    pile_etats.push_back(e);
    pile_symboles.push_back(s);
}

Automate::run() {
    Symbole * s = lexer->Consulter();
    while (pile_etats.back()->transition(*this, s)) {
        s = lexer->Consulter();
    }
}

Automate::popSymbole() {
    Symbole * s = pile_symboles.back();
    pile_symboles.pop_back();
    return s;
}


