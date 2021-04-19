#include "Segmento.h"

Segmento::Segmento(double x1, double y1, double x2, double y2, int esp, int c, int t) : FigBase(x1, y1, esp, c, t)
{
    setX2(x2);
    setY2(y2);
}

double Segmento::getX2() const
{
    return x2;
}
void Segmento::setX2(double x1)
{
    this->x2 = x1;
}
double Segmento::getY2() const
{
    return y2;
}
void Segmento::setY2(double y1)
{
    this->y2 = y1;
}
float Segmento::area() const
{
    return 0;
}
float Segmento::perimetro() const
{
    return sqrt((getX2() - getX())* (getX2() - getX()) + (getY2() - getY()) * (getY2() - getY()));
}
void Segmento::imprime() const
{
    cout << "--- [Segmento] ---" << endl;
    FigBase::imprime();
    cout << " x2 = " << getX2() << " y2 = " << getY2() << endl;
    cout << " area = " << area() << " perimetro = " << perimetro() << endl;
}

void Segmento::le()
{
    double x2,y2;
    cout << "entre com x,y,espessura,cor,tipo,x1,x2" << "\n" << "exatamente nessa ordem" << endl;
    FigBase::le();
    cin >> x2;
    setX2(x2);
    cin >> y2;
    setY2(y2);
}
ostream& operator << (ostream& os,const Segmento &s)
{
    s.imprime();
    return os;
}

istream& operator >> (istream& in, Segmento &s)
{
    s.le();
    return in;
}