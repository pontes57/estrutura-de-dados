
#include "Circulo.h"
const float PI = 3.141592653589;

Circulo::Circulo(double x, double y, double r,
                 int esp, int c, int t) : FigBase(x, y, esp, c, t)
{
    setRaio(r);
}

double Circulo::getRaio() const
{
    return raio;
}

void Circulo::setRaio(double r)
{
    raio = r;
}

float Circulo::area() const
{
    return PI * raio * raio;
}

float Circulo::perimetro() const
{
    return 2 * PI * raio;
}

void Circulo::imprime() const
{
    cout << "--- [Circulo] ---" << endl;
    FigBase::imprime();
    cout << " raio = " << getRaio() << endl;
    cout << " area = " << area() << " perimetro = " << perimetro() << endl;
}

void Circulo::le()
{
    double r;
    cout << "entre com x,y,espessura,cor,tipo,raio" << "\n" << "exatamente nessa ordem" << endl;
    FigBase::le();
    cin >> r;
    setRaio(r);
}
ostream& operator << (ostream& os,const Circulo &ci)
{
    ci.imprime();
    return os;
}

istream& operator >> (istream& in, Circulo &ci)
{
    ci.le();
    return in;
}