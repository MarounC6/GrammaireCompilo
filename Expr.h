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


class ExprBin : public Expr
{
    public:
        
        ExpressionBin(Expr* gauche, Expr* droite);
        
        virtual ~ExprBin();
        
        virtual double eval()=0;
    protected:
        
        Expr* gauche;
        Expr* droite;
};


class ExprPlus:public ExprBin
{
    public:
        ExprPlus(Expr* gauche, Expr* droite);
        ~ExprPlus();
        double eval();
};

class ExprMult:public ExprBin
{
    public:
        ExprMult(Expr* gauche, Expr* droite);
        ~ExprMult();
    double eval();
};

class ExprVal:public Expr
{
    public:
        ExprVal(int v);
        ~ExprVal(){};
        double eval();
    private:
        int valeur;
};