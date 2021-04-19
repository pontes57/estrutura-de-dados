#ifndef DATA_H
#define DATA_H
#include <iostream>
using namespace std;
class Data
{
friend ostream &operator<<(ostream &, const Data&);
friend istream &operator>>(istream &, Data&);
private:
    int dia;
    int mes;
    int ano;

public:
    Data(int d = 1, int m = 1, int a = 2018);
    Data(const Data &dt);
    void setDia(int const d);
    void setMes(int const m);
    void setAno(int const a);
    int getDia()const;
    int getMes()const;
    int getAno()const;
    int compData(const Data &dma)const;
    int difDias(const Data &dma)const;
    void imprime()const;
};
#endif