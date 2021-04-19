#include "FigBase.h"
#include <iostream>
#include <cmath>
using namespace std;
#ifndef SEGMENTO_H
#define SEGMENTO_H
class Segmento : public FigBase
{
    friend ostream& operator<< (ostream& os,const Segmento &s);
    friend istream& operator>> (istream& in, Segmento &s); 
private:
    double x2;
    double y2;

public:
    Segmento(double x1=0, double y1=0, double x2=0, double y2=0, int esp=1, int c=1, int t=1);
    double getX2() const;
    void setX2(double x);
    double getY2() const;
    void setY2(double y);
    float area() const;
    float perimetro() const;
    void imprime() const;
    void le();
};
#endif