#pragma once

#include <string>
#include "symbole.h"
using namespace std;

class Expr: public Symbole {
    public:
        Expr() : Symbole (EXPR) {}
        virtual ~Expr() {}
        virtual double eval() = 0;

        double getValeur();

    protected:
        double valeur;
}

