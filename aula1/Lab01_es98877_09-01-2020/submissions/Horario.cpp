#include <iostream>
#include "Horario.h"
using namespace std;

void Horario ::setHora(int const h)
{
    if (h > 23)
        hora = 23;
    else if (h < 0)
        hora = 0;
    else
        hora = h;
}

void Horario ::setMinuto(int const m)
{
    if (m > 59)
        minuto = 59;
    else if (m < 0)
        minuto = 0;
    else
        minuto = m;
}

void Horario ::setSegundo(int const s)
{
    if (s > 59)
        segundo = 59;
    else if (s < 0)
        segundo = 0;
    else
        segundo = s;
}

Horario ::Horario(int h, int m, int s)
{
    setHora(h);
    setMinuto(m);
    setSegundo(s);
}

Horario ::Horario(const Horario &hr)
{
    setHora(hr.hora);
    setMinuto(hr.minuto);
    setSegundo(hr.segundo);
}

int Horario ::getHora()const
{
    return hora;
}

int Horario ::getMinuto()const
{
    return minuto;
}

int Horario ::getSegundo()const
{
    return segundo;
}
int Horario ::compHorario(const Horario &hms)const
{
    if (hms.hora > hora)
        return -1;
    else if (hms.minuto > minuto)
        return -1;
    else if (hms.segundo > segundo)
        return -1;
    else if (hms.hora == hora && hms.minuto == minuto && hms.segundo == segundo)
        return 0;
    else
        return 1;
}
int Horario ::difSegundos(const Horario &hms)const
{
    return (segundo - hms.segundo + 60 * (minuto - hms.minuto) + 3600 * (hora - hms.hora));
}
void Horario ::imprime()const
{
    cout << getHora() << " " << getMinuto() << " " << getMinuto() << endl;
}

ostream& operator << (ostream& os,const Horario &h)
{
 os << h.getHora() << " " << h.getMinuto() << " " << h.getSegundo();
 return os;
}

istream& operator >> (istream& in, Horario &hora)
{
int h, m, s;
in >> h;
in >> m;
in >> s;
hora.setHora(h);
hora.setMinuto(m);
hora.setSegundo(s);
return in;
}