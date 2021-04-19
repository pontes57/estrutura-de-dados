#include <iostream>
#include "MySet.h"

using namespace std;

template <class T>
void procura(MySet<T> &s, T elem) {
	cout << "Procurando " << elem << " : " << (s.find(elem)!=s.end()) << endl;
}

template <class T>
void insere(MySet<T> &s, T elem) {
	cout << "Inserindo " << elem << " : " << (s.insert(elem).second) << endl;
	s.checkTree();
	cout << "Ainda AVL? " << s.checkIfAVL(true) << endl;
	s.imprimeBFS();
	cout << endl;
}

int main() {
	MySet<int> s;
	insere(s,1);
	insere(s,2);
	insere(s,10);
	insere(s,10); //repetidos..
	insere(s,10); //repetidos..
	insere(s,1);

	s.imprimeBFS();
	cout << endl;

	//qual sera o formato dessa arvore?
	//desenhe-a!
	MySet<char> s2;
	char inserir[] = {'S','T','X','E','B','M','G','N','J','Q','Z'};
	for(int i=0;i<sizeof(inserir)/sizeof(char);i++)
		insere(s2,inserir[i]);

	
	{
		MySet<char> s3 = s2;
		s3.imprimeBFS();
	}
	
}