#include "FigBase.h"

FigBase::FigBase(double x, double y, int esp, int c, int t)
{
    setX(x);
    setY(y);
    setEspessura(esp);
    setCor(c);
    setTipo(t);
}

double FigBase::getX() const
{
    return x;
}

void FigBase::setX(double x)
{
    this->x = x;
}

double FigBase::getY() const
{
    return y;
}

void FigBase::setY(double y)
{
    this->y = y;
}

int FigBase::getEspessura() const
{
    return espessura;
}

void FigBase::setEspessura(int esp)
{
    espessura = (esp < 1 || esp > 5) ? 1 : esp;
}

int FigBase::getCor() const
{
    return cor;
}

void FigBase::setCor(int c)
{
    cor = (c < 1 || c > 5) ? 1 : c;
}

int FigBase::getTipo() const
{
    return tipo;
}

void FigBase::setTipo(int t)
{
    tipo = (t < 1 || t > 3) ? 1 : t;
}

void FigBase::imprime() const
{
    cout << " Atributos da linha: " << endl;
    cout << "     Espessura = " << getEspessura() << endl;
    cout << "     Cor       = " << getCor() << endl;
    cout << "     Tipo      = " << getTipo() << endl;
    cout << " x = " << getX() << " y = " << getY() << endl;
}
void FigBase::le()
{
    double x,y;
    int esp,c,t;
    cin >> x;
    setX(x);
    cin >> y;
    setY(y);
    cin >> esp;
    setEspessura(esp);
    cin >> c;
    setCor(c);
    cin >> t;
    setTipo(t);
}