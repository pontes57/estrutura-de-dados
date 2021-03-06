#include <list>
#include <iostream>
#include "MyHashMap.h"
using namespace std;

#include <string>
using namespace std;

//functor que calcula o hash de um numero inteiro i
class MyStringHash {
public:
	unsigned operator()(const string &s) const { //nesse exemplo, temos que hash(i) = i
		return (int)s[0];
	}
};

//Exercicio: crie outras funcoes hash e teste-as!

int main() {
	MyHashMap<string,int,MyStringHash > map;
	map.set("Jose da Silva",1230);
	map.set("Joaquim",1391);
	map.set("Maria Silva",9211);
	map.set("Fernando Ferreira",79);
	map.set("Arthur Bernardes",98);
	map.set("Salles Magalhaes",96);
	map.set("Abc da Silva",6);
	map.set("Renata Gomes",22);
	map.set("Patricia Sousa",123);
	map.set("Ligia Soares",1234);
	map.imprime();

	cout << "Quantas pessoas com matricula nome Joaquim? " << map.count("Joaquim") << endl;
	cout << "Quantas pessoas com nome Joaquinho? " << map.count("Joaquinho") << endl;
	cout << "Matricula de Salles? " << map.getValue("Salles Magalhaes") << endl;
}