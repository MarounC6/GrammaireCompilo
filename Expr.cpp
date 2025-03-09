#include "Expr.h"
#include <iostream>
using namespace std;

//Retourne la valeur de l'expression
double Expr::getValeur()
{
    return valeur;
}


//Initialise l'expression
ExprBin::ExprBin(Expr* l1, Expr* r1)
{
    gauche=l1;
    droite=r1;
}

//Attribue une valeur lors de la construction
ExprMult::ExprMult(Expr* l1, Expr* r1):ExprBin(l1,r1)
{
    valeur=eval();
}

//Attribue une valeur lors de la construction
ExprPlus::ExprPlus(Expr* l1,Expr* r1):ExprBin(l1,r1)
{
    valeur=eval();
}

//Attribue une valeur lors de la construction
ExprVal::ExprVal(int v1)
{
    valeur=v1;
}

//Retourne le produit de l'expression droite et de l'expression gauche
double ExprMult::eval()
{
    return gauche->eval()*droite->eval();
}

//Retourne la somme de l'expression droite et de l'expression gauche
double ExprPlus::eval()
{
    return gauche->eval()+droite->eval();
}

//Retourne la valeur de l'expression
double ExprVal::eval()
{
    return (double) valeur;
}

ExprBin::~ExprBin()
{
    //delete gauche;
    //delete droite;
}

ExprMult::~ExprMult()
{
    //delete gauche;
    //delete droite;
}

ExprPlus::~ExprPlus()
{
    //delete gauche;
    //delete droite;
}