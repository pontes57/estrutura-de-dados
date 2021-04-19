#ifndef Conjunto_H
#define Conjunto_H

#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
class Conjunto;

template <class T>
ostream &operator<<(ostream &os,const Conjunto<T> &elementos);
template <class T>
istream& operator>>(istream &in,Conjunto<T> &elementos); 

template <class T>
class Conjunto {

	friend ostream &operator<< <T>(ostream &os,const Conjunto<T> &elementos);
	friend istream &operator>> <T>(istream &in,Conjunto<T> &elementos);
public:
	Conjunto(int n=10);
	~Conjunto();
	Conjunto(const Conjunto&other);
	const Conjunto &operator=(const Conjunto&other);
	bool operator==(const Conjunto<T> &other) const;
	bool insere(const T &x);   
	int numelementos()const;
	bool pertence(const T e)const;

private:
	int tam_array;
	T *elementos;
	int num_elementos=0;
};


template <class T>
Conjunto<T>::~Conjunto() {
	delete []elementos;
}

template <class T>
const Conjunto<T> & Conjunto<T>::operator=(const Conjunto<T>&other) {
	if(&other==this) return *this;
	delete []elementos;
	tam_array = other.tam_array;
	elementos = new T[tam_array];
	num_elementos=other.num_elementos;
	for(int i=0;i<tam_array;i++) elementos[i]= other.elementos[i];
	return *this;
}

template <class T>
Conjunto<T>::Conjunto(const Conjunto<T>&other) {
	tam_array = other.tam_array;
	elementos = new T[tam_array];
	num_elementos=other.num_elementos;
	for(int i=0;i<tam_array;i++) elementos[i]= other.elementos[i];
}

template <class T>
Conjunto<T>::Conjunto(int n): tam_array(n) {
	elementos = new T[n];
	tam_array==n;
}

template <class T>
ostream &operator<<(ostream &os,const Conjunto<T> &elementos) {
	os << "{";
	for(int i=0;i<elementos.num_elementos-1;i++){
	 	os << elementos.elementos[i] << ","; 
	}
	if(elementos.num_elementos>0){
		os << elementos.elementos[elementos.num_elementos-1];
	}
	os << "}";

	return os;
}
template <class T>
istream& operator>>(istream &in,Conjunto<T> &e){
	T temp;
	while (in>>temp)
	{
		e.insere(temp);
	}
	return in;
}
template <class T>
bool Conjunto<T>::operator==(const Conjunto<T> &other) const{
	if(num_elementos!=other.num_elementos) {
		return false;
	}
	for(int i=0;i<num_elementos;i++)
		if(!pertence(other.elementos[i])) 
			return false;
	return true;
}

template <class T>
bool  Conjunto<T>::insere(const T &x){
	if(num_elementos==tam_array){
		return false;
	}
	if(pertence(x)){
		return false;
	}
	elementos[num_elementos]=x;
	num_elementos++;
	return true;
}
template <class T>
bool Conjunto<T>::pertence(const T e)const{
	for (int i = 0; i < num_elementos; i++){
		if (elementos[i]==e)
		{
		return true;
		}
	}
	return false;
}

template <class T>
int Conjunto<T>::numelementos()const{
	return num_elementos;
}

#endif
