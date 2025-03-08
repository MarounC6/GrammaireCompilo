#pragma once

#include <string>
#include <vector>
#include "lexer.h"
#include "symbole.h"
#include "Etat.h"

using namespace std;


class Automate {
    public:
        Automate(Lexer* l);

        virtual ~Automate();

        void decalage(Symbole * s, Etat * e);

        void reduction(int n, Symbole * s);

        void transitionSimple(Symbole * s, Etat * e);

        void run();

        Symbole* popSymbole();

        void eval();


    protected:
        Lexer * lexer;
        vector<Etat*> pile_etats;
        vector<Symbole*> pile_symboles;
};