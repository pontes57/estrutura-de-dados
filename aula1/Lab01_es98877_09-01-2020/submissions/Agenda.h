#ifndef AGENDA_H
#define AGENDA_H
#include <iostream>
#include <string>
#include "Horario.h"
#include "Data.h"
using namespace std;
class ItemAgenda
{
private:
    string descricao;
    Data d;
    Horario h;
public:
    ItemAgenda();
    ItemAgenda(const string &desc,const Data &dt,const Horario &hr);
    ItemAgenda(const ItemAgenda &it);
    void setDesc(const string &desc);
    void setData(const Data &dt);
    void setHorario(const Horario &dhr);
    const string &getDesc()const;
    const Data &getData()const;
    const Horario & getHorario()const;
};
class Agenda
{
private:
    ItemAgenda vetor[100];
    static int cont;
public:
    Agenda();
    void inserirItem(const ItemAgenda &it);
    void compromissosData(const Data &d)const;
};
#endif
