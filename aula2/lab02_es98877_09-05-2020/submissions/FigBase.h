#ifndef FIGBASE_H
#define FIGBASE_H
#include <iostream>
using namespace std;

class FigBase
{
private:
    double x;
    double y;
    int espessura;
    int cor;
    int tipo;

public:
    FigBase(double x, double y, int esp, int c, int t);
    double getX() const;
    void setX(double x);
    double getY() const;
    void setY(const double y);
    int getEspessura() const;
    void setEspessura(int esp);
    int getCor() const;
    void setCor(int c);
    int getTipo() const;
    void setTipo(int t);
    void imprime() const;
    void le();
};
#endif