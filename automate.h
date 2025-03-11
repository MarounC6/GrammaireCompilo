#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <string>
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

        void addSymboleToDelete(Symbole * s);

        Lexer * getLexer(){
            return lexer;
        }

        void setError(string message){
            error_message = message;
        }

        string getError(){
            return error_message;
        }


    protected:
        Lexer * lexer;
        vector<Etat*> pile_etats;
        vector<Symbole*> pile_symboles;
        vector<Symbole*> pile_symboles_to_delete;
        string error_message;
};