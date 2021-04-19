
#include "Retangulo.h"
Retangulo::Retangulo(double x, double y,
                     double larg, double alt,
                     int esp, int c, int t) : FigBase(x, y, esp, c, t)
{
    setLargura(larg);
    setAltura(alt);
}
double Retangulo::getLargura() const
{
    return largura;
}

void Retangulo::setLargura(double larg)
{
    largura = larg;
}
double Retangulo::getAltura() const
{
    return altura;
}

void Retangulo::setAltura(double alt)
{
    altura = alt;
}

float Retangulo::area() const
{
    return altura * largura;
}

float Retangulo::perimetro() const
{
    return 2 * (largura + altura);
}

void Retangulo::imprime() const
{
    cout << "--- [Retangulo] ---" << endl;
    FigBase::imprime();
    cout << " largura = " << getLargura() << " altura = " << getAltura() << endl;
    cout << " area = " << area() << " perimetro = " << perimetro() << endl;
}

void Retangulo::le()
{
    double l,a;
    cout << "entre com x,y,espessura,cor,tipo,largura,altura" << "\n" << "exatamente nessa ordem" << endl;
    FigBase::le();
    cin >> l;
    setLargura(l);
    cin >> a;
    setAltura(a);
}

ostream& operator << (ostream& os,const Retangulo &r)
{
    r.imprime();
    return os;
}

istream& operator >> (istream& in, Retangulo &r)
{
    r.le();
    return in;
}