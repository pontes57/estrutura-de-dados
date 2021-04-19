#include <iostream>
#include "Data.h"
using namespace std;

void Data ::setDia(int const d)
{
    if (d > 30)
        dia = 30;
    else if (d < 1)
        dia = 1;
    else
        dia = d;
}

void Data ::setMes(int const m)
{
    if (m > 12)
        mes = 12;
    else if (m < 1)
        mes = 1;
    else
        mes = m;
}

void Data ::setAno(int const a)
{
    if (a > 2020)
        ano = 2020;
    else if (a < 2018)
        ano = 2018;
    else
        ano = a;
}

Data ::Data(int d, int m, int a)
{
    setDia(d);
    setMes(m);
    setAno(a);
}

Data ::Data(const Data &dt)
{
    this->dia = dt.dia;
    this->ano = dt.ano;
    this->mes = dt.mes;
}

int Data ::getDia() const
{
    return dia;
}

int Data ::getMes()const
{
    return mes;
}

int Data ::getAno()const
{
    return ano;
}
int Data ::compData(const Data &dma)const
{
    if (dma.ano > ano)
        return -1;
    else if (dma.mes > mes)
        return -1;
    else if (dma.dia > dia)
        return -1;
    else if (dma.ano == ano && dma.mes == mes && dma.dia == dia)
        return 0;
    else
        return 1;
}
int Data ::difDias(const Data &dma)const
{
    return (dia - dma.dia + 30 * (mes - dma.mes) + 360 * (ano - dma.ano));
}
void Data ::imprime()const
{
    cout << dia << " " << mes << " " << ano << endl;
}

ostream &operator<<(ostream &out,const Data &data)
{
out << data.getDia() << " " << data.getMes() << " " << data.getAno();
return out;
}

istream &operator>>(istream &in, Data&data)
{
int d, m, a;
in >> d >> m >> a;
data.setMes(m);
data.setAno(a);
data.setDia(d);
return in;
}