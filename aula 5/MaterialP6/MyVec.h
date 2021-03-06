/*
TAD MyVec
- Representa uma lista implementada por contiguidade
- Interface similar a da classe Vector do STL
- Criado por Salles Magalhaes em 19/02/2018

*/

#ifndef MyVec_H__
#define MyVec_H__

#include <iostream>
#include <string>
#include <ostream>


//Excessao usada pela classe MyVec
class MyVecException {
private:
	std::string msg;
public:
	MyVecException (const std::string &msg0): msg(msg0) { }
	const std::string & what() const { return msg; }
};


template<class T>
class MyVec {
public:
	template<class T2>
	friend std::ostream& operator<<(std::ostream &, const MyVec<T2> &);

	//construtores/destrutures/etc
	MyVec();
	MyVec(int n, const T&init=T());

	//destrutor
	~MyVec() { destroy(); };

	//Construtor de copia
	MyVec(const MyVec &);
	MyVec & operator=(const MyVec &);

	//funcoes de acesso
	T &operator[](int pos) {return data[pos];}
	const T &operator[](int pos) const {return data[pos];}
	void push_back(const T&);
	int eraseMatchingElements(const T&);
	void resize(int newSize);
	void insert(const T&,int pos);
	void sortedInsert(const T&elem);
	void clear();

	void empty() const {return size() == 0;};
	int size() const {return dataSize;};


private:
	T *data; //declare o membro de dados data, que devera armazenar os elementos da lista
	int dataSize; //quantos elementos ha na lista?
	int dataCapacity; //quantos elementos atualmente cabem na lista? 

	void create();
	void destroy();
	void resizeCapacity(int newCapacity);
};

template<class T>
void MyVec<T>::push_back(const T&elem) {
	if(dataSize == dataCapacity) {
		if(dataCapacity ==0) {
			resizeCapacity(1);
			data[0]=elem;
			dataSize++;
			return;
		}
		else
			resizeCapacity(dataCapacity*2);
	}
	data[dataSize]=elem;
	dataSize++;

}
//A função é O(n),nao sendo possivel ser mais eficiente.
template<class T>
int MyVec<T>::eraseMatchingElements(const T&elem){
	int contador=0;
	for (int i = 0; i < dataSize; i++)
	{
		if (data[i]==elem)
		{
			contador++;
		}
		else
		{
			data[i-contador]=data[i];
		}	
	}
	dataSize=dataSize-contador;
	return contador;
}

template<class T>
void MyVec<T>::resize(int newSize) {
	if(newSize >= dataCapacity) { //primeiro temos que realocar o vector...
		resizeCapacity(newSize); //para o resize vamos usar o tamanho exato caso seja necessario realocar o vector..
	}
	for(int i=dataSize;i<newSize;i++) { //preencha a parte "extra" do vector com valores "em branco"
		data[i] = T();
	}
	dataSize = newSize;
}

//insere o elemento na posicao pos e move os elementos ja presentes no vetor
// pos pode ser:
//   uma posicao apos o final do vetor (para inserir na ultima posicao) 
//   ou uma posicao ja existente (nesse caso os elementos nessa posicao e apos ela serao movidos "para a frente")
template<class T>
void MyVec<T>::insert(const T&elem,int pos) {
	if(pos > dataSize || pos < 0) {
		throw MyVecException("Erro na funcao insert: posicao invalida");
	}

	if(dataSize == dataCapacity) { //preciso redimensionar?
		if(dataCapacity ==0) //Exercicio: Por que e' preciso testar isso?
			resizeCapacity(1);
		else
			resizeCapacity(dataCapacity*2);
	}	

	for(int i=dataSize;i>pos;i--)
		data[i] = data[i-1];
	data[pos] = elem;
	dataSize++;
}

template<class T>
void MyVec<T>::sortedInsert(const T&elem) {
	if (dataCapacity==0)
	{
		insert(elem,0);
	}
	else
	{
		for (int i = 0; i < dataSize; i++)
		{
			if (data[i]>elem)
			{
				insert(elem,i);
				return;
			}
			
		}
		insert(elem,dataSize);
		
	}
}

template<class T>
void MyVec<T>::clear() {
	destroy();
	create();
}


template<class T>
void MyVec<T>::resizeCapacity(int newCapacity) {
	if (dataCapacity>=newCapacity){return;}
	T*temp =new T[newCapacity];
	for(int i=0;i<dataSize;i++) temp[i] = data[i];
	dataCapacity=newCapacity;
	delete[]data;
	data=temp;
}

template<class T>
void MyVec<T>::destroy() {
	delete []data;
	dataSize = dataCapacity = 0;
}

template<class T>
void MyVec<T>::create() {
	data = NULL;
	dataSize = dataCapacity = 0;
}

template<class T>
MyVec<T>::MyVec() {
	create();
}

template<class T>
MyVec<T>::MyVec(int n, const T&init) {
	data=new T[n];
	dataSize=dataCapacity=n;
	for(int i=0;i<dataCapacity;i++)	data[i] = init;
}


//Construtor de copia
template<class T>
MyVec<T>::MyVec(const MyVec &other) {
	data=NULL;
	*this=other;

}

template<class T>
MyVec<T> & MyVec<T>::operator=(const MyVec &other) {
	if(this==&other) return *this; 
	destroy(); //Exercicio: por que precisamos disso?
	dataCapacity = other.dataCapacity;
	dataSize = other.dataSize;
	//data = other.data; //por que nao podemos fazer isso?
	data = new T[dataCapacity];
	for(int i=0;i<dataSize;i++) data[i] = other.data[i];
	return *this;
}

template<class T2>
std::ostream& operator<<(std::ostream &out, const MyVec<T2> &v) {
	out << "Size: " << v.size() << "\n";
	out << "Capacity: " << v.dataCapacity << "\n";
	for(int i=0;i<v.size();i++) out << v.data[i] << " ";
	out << "\n";
	return out;
}

#endif