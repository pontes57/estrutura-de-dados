#include "FigBase.h"
#include <iostream>
using namespace std;
#ifndef __Circulo_h
#define __Circulo_h

class Circulo : public FigBase
{
    friend ostream& operator<< (ostream& os,const Circulo &ci);
    friend istream& operator>> (istream& in, Circulo &ci); 
private:
    double raio;

public:
    Circulo(double x=0, double y=0, double r=0,int esp=0, int c=0, int t=0);
    double getRaio() const;
    void setRaio(double);
    float perimetro() const;
    float area() const;
    void imprime() const;
    void le();
};

#endif
