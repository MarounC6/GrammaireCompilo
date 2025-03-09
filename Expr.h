#pragma once

#include <string>
#include "symbole.h"
using namespace std;

//Classe abstraite
class Expr: public Symbole {
    public:
        Expr() : Symbole (EXPR) {}
        virtual ~Expr() {}
        virtual double eval() = 0; //Méthode virtuelle pure qui sera redéfinie dans les classes filles

        double getValeur();

    protected:
        double valeur;
};


class ExprBin : public Expr
{
    public:
        
        ExprBin(Expr* gauche, Expr* droite);
        
        virtual ~ExprBin();
        
        virtual double eval()=0; //Méthode virtuelle pure qui sera redéfinie dans les classes filles
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