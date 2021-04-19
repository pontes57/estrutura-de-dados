#include "Agenda.h"


ItemAgenda :: ItemAgenda(const string &desc,const Data &dt,const Horario &hr)
{
    setDesc(desc);
    setData(dt);
    setHorario(hr);
}

ItemAgenda :: ItemAgenda(){}

ItemAgenda :: ItemAgenda(const ItemAgenda &it)
{
    setDesc(it.descricao);
    setData(it.d);
    setHorario(it.h);   
}

void ItemAgenda :: setDesc(const string &desc)
{
    descricao=desc;
}

void ItemAgenda :: setData(const Data &dt)
{  
    d.setDia(dt.getDia());
    d.setMes(dt.getMes());
    d.setAno(dt.getAno());
}

void ItemAgenda :: setHorario(const Horario &dhr)
{
    h.setHora(dhr.getHora());
    h.setMinuto(dhr.getMinuto());
    h.setSegundo(dhr.getSegundo());
}

const string &ItemAgenda :: getDesc() const
{
    return descricao;
}

const Data & ItemAgenda :: getData() const
{
    return d;
}

const Horario & ItemAgenda :: getHorario()const
{
    return h;
}

Agenda :: Agenda(){}

void Agenda :: inserirItem(const ItemAgenda &it)
{
    vetor[cont]=it;
    cont++;
}

int Agenda :: cont=0;

void Agenda :: compromissosData(const Data &d)const
{   
    for (int i = 0; i < cont; i++)
    {
        if (vetor[i].getData().getDia()==d.getDia() && vetor[i].getData().getMes()==d.getMes() && vetor[i].getData().getAno()==d.getAno())
        {
         cout << vetor[i].getHorario() << " " << vetor[i].getDesc() << endl;
        }
    }
}

