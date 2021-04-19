#ifndef Conjunto_H
#define Conjunto_H

#include <iostream>
#include <cstdlib>
using namespace std;

//precisamos declarar que a classe Conjunto existe para que possamos utiliza-la na declaracao
//do operador << abaixo...
template <class T>
class Conjunto;

//precisamos declarar a existencia do operador << do tipo T antes de poder
//declarar que ele e' friend da classe(abaixo)
//Ha outras alternatielementosas para declarar o operador << friend, mas elas possuem alguns problemas
//Ha muita elementosariacao sobre as exigencias dos compiladores a respeito de templates/friend
template <class T>
ostream &operator<<(ostream &os,const Conjunto<T> &elementos);
template <class T>
istream& operator>>(istream &in,Conjunto<T> &elementos); 

template <class T>
class Conjunto {

	friend ostream &operator<< <T>(ostream &os,const Conjunto<T> &elementos);
	friend istream &operator>> <T>(istream &in,Conjunto<T> &elementos); // o operador nao e' friend de Conjunto... e' friend do Conjunto de T! 
public:
	Conjunto(int n=10);
	~Conjunto();
	const Conjunto &operator=(const Conjunto&other);
	Conjunto(const Conjunto&other);

	T &operator[](int i) { return elementos[i]; } //implementada no cabecalho...
	const T& operator[](int) const; //elementosersao constante do operador acima...
													        //T pode ser grande --> retornar por referencia!

	//nao existe mais a classe "Conjunto"... existe "Conjunto de T"
	Conjunto<T> operator+(const Conjunto<T> &other) const; //soma o Conjunto "this" com other, retornando o resultado
	bool operator==(const Conjunto<T> &other) const; //elementoserifica se o Conjunto e' igual ao outro
	bool operator!=(const Conjunto<T> &other) const;
	bool insere(const T &x);   
	int numelementos();
	bool pertence(T e);

private:
	int num_array;
	T *elementos;
	int num_elementos=0;
};


template <class T>
Conjunto<T>::~Conjunto() {
	delete []elementos;
}

template <class T>
const Conjunto<T> & Conjunto<T>::operator=(const Conjunto<T>&other) {
	if(&other==this) return *this; //testa auto-atribuicao...
	delete []elementos;
	num_array = other.num_array;
	elementos = new T[num_array];
	num_elementos=other.num_elementos;
	for(int i=0;i<num_array;i++) elementos[i]= other.elementos[i];
	return *this;
}

template <class T>
Conjunto<T>::Conjunto(const Conjunto<T>&other) {
	num_array = other.num_array;
	elementos = new T[num_array];
	num_elementos=other.num_elementos;
	for(int i=0;i<num_array;i++) elementos[i]= other.elementos[i];
}

//Definicao em C++ nao podem estar em arquielementosos .cpp (ao incluir o header
//em um .cpp o compilador precisa instanciar a classe imedianum_arrayente -- nao 
// eh possielementosel compilar de forma separada)
//Exemplo: se houelementosesse um .cpp contendo a implementacao de Conjunto com templates, ao
//compilar esse .cpp de forma separada como o compilador saberia quais os tipos a serem usados
//no lugar de T?

//precisamos desse cabecalho em todas funcoes declaradas fora da classe
template <class T>
Conjunto<T>::Conjunto(int n): num_array(n) {
	elementos = new T[n];	//construtor padrao to tipo T . Inteiros, float, char, etc. elementosalem 0 por padrao.
	num_array==n;
}

template <class T>
ostream &operator<<(ostream &os,const Conjunto<T> &elementos) {
	cout << "{";
	for(int i=0;i<elementos.num_elementos-1;i++){
	 	os << elementos.elementos[i] << ","; 
		}
	cout << elementos.elementos[elementos.num_elementos-1] << "}";

	return os;
}
template <class T>
istream& operator>>(istream &in,Conjunto<T> &e){
	T temp;
	for(int i=0;i<e.num_array;i++){
		in >> temp;
		if (e.pertence(temp)==true){
			continue;
		}

		e.elementos[e.num_elementos]=temp;

		if (e.elementos[e.num_elementos]!=false)
		{
			e.num_elementos++;
		}
	}
	return in;
}

template <class T>
const T& Conjunto<T>::operator[](int i) const { //elementosersao constante do operador acima...
	return elementos[i];
}

template <class T>
Conjunto<T> Conjunto<T>::operator+(const Conjunto<T> &other) const{ //soma o Conjunto "this" com other, retornando o resultado
    Conjunto<T>B(num_array+other.num_array);
    num_array=num_array+other.num_array;
    B=*this;
    num_array=num_array-other.num_array;
    for (int i = 0; i <other.num_elementos; i++)
    {
        B.insere(other.elementos[i]);
    }
    return B;
}

template <class T>												        //o Conjunto "this" nao eh modificado
bool Conjunto<T>::operator!=(const Conjunto<T> &other) const{ //elementoserifica se o Conjunto e' igual ao outro
	return !(*this == other); 
}

template <class T>
bool Conjunto<T>::operator==(const Conjunto<T> &other) const{
	if(num_array!=other.num_array) {
		return false; // num_arrayanho diferente --> Conjuntoes diferentes!
	}
	for(int i=0;i<num_array;i++)
		if(elementos[i]!=other.elementos[i]) 
			return false;
	return true;
}

template <class T>
bool  Conjunto<T>::insere(const T &x){
	if(num_elementos==num_array){
		return false;
	}
	if(pertence(x)){
		return false;
	}
	for (int i = 0; i < num_elementos; i++){
		if (elementos[i]==x)
		{
			return false;
		}
		
	}
	elementos[num_elementos]=x;
	num_elementos++;
	return true;
}

template <class T>
bool Conjunto<T>::pertence(T e){
	for (int i = 0; i < num_elementos; i++){
		if (elementos[i]==e)
		{
		return true;
		}
	}
	return false;
}

template <class T>
int Conjunto<T>::numelementos(){
	return num_elementos;
}

#endif
