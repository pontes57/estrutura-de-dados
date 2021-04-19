#include "FigBase.h"
#include <iostream>
using namespace std;
#ifndef __Retangulo_h
#define __Retangulo_h
class Retangulo : public FigBase
{
    friend ostream& operator<< (ostream& os,const Retangulo &r);
    friend istream& operator>> (istream& in, Retangulo &r); 
private:
    double largura, altura;

public:
    Retangulo(double=0, double=0, double=0, double=0, int=0, int=0, int=0);
    double getLargura() const;
    void setLargura(double larg);
    void setAltura(double alt);
    double getAltura() const;
    float area() const;
    float perimetro() const;
    void imprime() const;
    void le();
};

#endif
