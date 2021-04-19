#include <iostream>
#include "MyVec.h"
#include <stdlib.h>
using namespace std;


class ArvoreExpressao {
public:
	void imprimeArrays() const;

	void leArvore();
	void imprimeExpressao() const;
	int avaliaValor() const;
	int altura() const;
	int nivelMaisNodos() const;
	int avaliaValor1(int pos) const;
	void imprimeExpressao1(int pos) const;
	int altura1(int pos) const;
	void nivelMaisNodos1(int vec[],int pos,int count) const;

private:
	//Nao adicione nenhum membro de dados na sua classe!!!!
	//Funcoes auxiliares podem ser adicionadas se necessario.

	MyVec<int> filhoEsquerdo;
	MyVec<int> filhoDireito;
	MyVec<char> operador;
};

void ArvoreExpressao::imprimeArrays() const {
	for(int i=0;i<filhoEsquerdo.size();i++) cout << i << " "; cout << "\n";
	for(int i=0;i<filhoEsquerdo.size();i++) cout << filhoEsquerdo[i] << " "; cout << "\n";
	for(int i=0;i<filhoDireito.size();i++) cout << filhoDireito[i] << " "; cout << "\n";
	for(int i=0;i<operador.size();i++) cout << operador[i] << " "; cout << "\n";
}

/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
//sua implementacao:


void ArvoreExpressao::leArvore() {
	int n,p,e,d;
	char o;
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> p;
		cin >> e;
		cin >> d;
		cin >> o;
		filhoEsquerdo.insert(e,p);
		filhoDireito.insert(d,p);
		operador.insert(o,p);
	}
}


int ArvoreExpressao:: avaliaValor1 (int pos) const{
	if (operador[pos]=='+'){
		return (avaliaValor1(filhoEsquerdo[pos])+avaliaValor1(filhoDireito[pos]));
	}
	else if (operador[pos]=='-'){
		return (avaliaValor1(filhoEsquerdo[pos])-avaliaValor1(filhoDireito[pos]));
	}
	else if (operador[pos]=='*'){
		return (avaliaValor1(filhoEsquerdo[pos])*avaliaValor1(filhoDireito[pos]));
	}
	else{
		char ajuda=operador[pos];
		return atoi(&ajuda);
	}
}

void ArvoreExpressao::imprimeExpressao1(int pos) const {
	if (operador.size()==1){
		cout << operador[pos];
		return;
	}
	if (pos==0){
		imprimeExpressao1(filhoEsquerdo[pos]);
		cout << operador[pos];
		imprimeExpressao1(filhoDireito[pos]);
	}
	else if (operador[pos]=='+'||operador[pos]=='-'||operador[pos]=='*'){
		cout << "(";
		imprimeExpressao1(filhoEsquerdo[pos]);
		cout << operador[pos];
		imprimeExpressao1(filhoDireito[pos]);
		cout << ")";
	}
	else{
		cout << operador[pos];
	}
}

int ArvoreExpressao::altura1(int pos) const {
	if (operador[pos]=='+'||operador[pos]=='-'||operador[pos]=='*'){
		int e=altura1(filhoEsquerdo[pos]);
		int d=altura1(filhoDireito[pos]);
		if (e>d) return e+1;
		else return d+1;
	}
	else return 0;
}

void ArvoreExpressao::nivelMaisNodos1(int vec[],int pos,int count) const {
	if (operador[pos]=='+'||operador[pos]=='-'||operador[pos]=='*'){
		nivelMaisNodos1(vec,filhoEsquerdo[pos],count+1);
		nivelMaisNodos1(vec,filhoDireito[pos],count+1);
	}
	vec[count]++;
}

void ArvoreExpressao::imprimeExpressao() const {
	imprimeExpressao1(0);
}

int ArvoreExpressao::avaliaValor() const {
	return avaliaValor1(0);
}

int ArvoreExpressao::altura() const {
	return altura1(0);
}

int ArvoreExpressao::nivelMaisNodos() const {
	int altura=(this->altura()+1);
	if (altura==0){
		return 1;
	}
	int vec[altura]={0};
	nivelMaisNodos1(vec,0,0);
	int maior=0;
	int pos;
	for (int i = 0; i < altura; i++){
		if(vec[i]>maior){
			maior=vec[i];
			pos=i;
		}
	}
	return (pos+1);
}




/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/

//Nao modifique aqui
//OBS: cada arquivo de teste começa com a descricao de uma arvore.
//A seguir, ha um numero indicando qual etapa sera testada...
int main() {
	ArvoreExpressao a;
	a.leArvore();

	int etapa;
	cin >> etapa; 
	switch(etapa) {
		case 1:
			cout << "Etapa 1:" << endl;
			a.imprimeArrays();
			break;
		case 2:
			cout << "Etapa 2:" << endl;
			a.imprimeExpressao();
			cout << endl;
			break;
		case 4:
			cout << "Etapa 4:" << endl;
			cout << a.avaliaValor() << endl;
			break;
		case 5:
			cout << "Etapa 5:" << endl;
			cout << a.altura() << endl;
			cout << a.nivelMaisNodos() << endl;
			break;
		default:
			cout << "Erro! Etapa invalida" << endl;
			break;
	}

}