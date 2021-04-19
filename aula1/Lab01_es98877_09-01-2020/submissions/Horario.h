#ifndef HORARIO_H
#define HORARIO_H
#include <iostream>
using namespace std;
class Horario
{
    friend ostream& operator<< (ostream& os,const Horario &h);
    friend istream& operator>> (istream& os, Horario &h); 
private:
    int hora;
    int minuto;
    int segundo;

public:
    Horario(int h=0,int m=0,int s=0);
    Horario(const Horario &hr);
    void setHora(int const h);
    void setMinuto(int const m);
    void setSegundo(int const s);
    int getHora() const;
    int getMinuto() const;
    int getSegundo() const;
    int compHorario(const Horario &hms) const;
    int difSegundos(const Horario &hms) const;
    void imprime() const; 
};
#endif
