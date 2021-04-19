#ifndef MY_SET_LIST_H
#define MY_SET_LIST_H

#include <algorithm> //classe pair esta aqui...
using namespace std;

template<class T>
class MySetIterator;

template  <class T>
class Node {
	public: //classe auxiliar.. vamos utiliza-la apenas neste arquivo (nao e' muito necessario ter encapsulamento)
		Node(const T &elem_) : elem(elem_),left(NULL), right(NULL), fb(0) {}
		Node<T> *left, *right;
		T elem;
		Node<T> *parent; //agora cada nodo armazena seu pai
		int fb;
};

template  <class T>
class MySet {
public:
	typedef MySetIterator<T> iterator;

	int size() const;
	MySet() : size_(0), root(NULL) {}

	pair<iterator,bool> insert(const T&elem); //retorna um iterador para o elemento inserido (o valor booleano sera' true se o elemento nao existia no conjunto e falso caso ele ja exista (ou seja, o novo elemento nao foi inserido) ).
	iterator find(const T&elem); //por simplicidade, nao vamos deixar implementar um find constante...

	iterator end() {return iterator(NULL);}; 
	iterator begin() ;

	MySet(const MySet &other);
	MySet &operator=(const MySet &other);
	~MySet();

	//operacoes de remocao nao suportadas na nossa implementacao de AVL (e' possivel adicionar, mas o balanceamento e' um pouco mais dificil do que o da insercao)

	void checkTree() const; //funcao para verificar a integridade da arvore! (usada para debugging)

	void imprimeBFS() const;
	void imprimeDFS_pre() const;
	void imprimeDFS_in() const;
	void imprimeDFS_pos() const;

	bool checkIfAVL(bool printFB=false) const; //printFB: se true imprime o fator de balanceamento de cada nodo... se a arvore nao for AVL nem todos FBs serao impressos..
private:
	Node<T> *root;
	int size_;

	bool checkIfAVL(const Node<T> *root, int &altura, bool printFB) const; //verifica recursivamente se a arvore eh AVL e tambem retorna a altura (caso a arvore seja AVL!) da subarvore com raiz em root
	void checkTree(const Node<T> *root) const;
	//funcoes auxiliares...
	pair<iterator,bool> insert(const T&elem, Node<T> *&root,bool &aumentouAltura, Node<T> *parent); 
	iterator find(const T&elem, Node<T> *root);

	void deleteNodes(Node<T> *root);
	Node<T> * copyNodes(const Node<T> *root, Node<T> *parent) const;

	void imprimeDFS_pre(const Node<T> *root) const;
	void imprimeDFS_in(const Node<T> *root) const;
	void imprimeDFS_pos(const Node<T> *root) const;
};





//por enquanto vamos desconsiderar os operadores ++ e -- em conjuntos...
//tais operadores serao "escondidos"
template<class T>
class MySetIterator {
	friend class MySet<T>;
public:
	MySetIterator(Node<T> *ptr_): ptr(ptr_) { }
	T &operator*() {return ptr->elem;}

	bool operator==(const MySetIterator &other) const {return ptr==other.ptr;}
	bool operator!=(const MySetIterator &other) const {return ptr!=other.ptr;}

	MySetIterator operator++();
	MySetIterator operator++(int);

	MySetIterator operator--();
	MySetIterator operator--(int);
private:
	Node<T> *ptr;
};


//operador de pre-incremento
template<class T>
MySetIterator<T>  MySetIterator<T>::operator++() {
	if(ptr->right) { //pegue o menor elemento da sub-arvore direita
		ptr = ptr->right;
		while(ptr->left) ptr=ptr->left;
	} else { //mais dificil..temos que subir na arvore ate fazermos a primeira virada a direita
		while(ptr->parent && ptr->parent->right==ptr) ptr = ptr->parent;  //enquanto vou a esquerda para chegar a meu pai, suba...
		ptr = ptr->parent;	//vire a direita (subindo) uma vez

		//para que precisamos do "ptr->parent &&" no while?
		//O que acontece se incrementarmos um iterador para o ultimo elemento da arvore?
	}
	return *this;
}

//operador de pre-decremento
template<class T>
MySetIterator<T>  MySetIterator<T>::operator--() {
	//faca tudo que fez no operador ++, mas no sentido contrario (left --> right e vice-versa)!
	if(ptr->left) { 
		ptr = ptr->left;
		while(ptr->right) ptr=ptr->right;
	} else { 
		while(ptr->parent && ptr->parent->left==ptr) ptr = ptr->parent;  
		ptr = ptr->parent;	

		//para que precisamos do "ptr->parent &&" no while?
		//O que acontece se decrementarmos um iterador para o primeiro elemento?
		//O que acontece se decrementarmos um apontador para end()?		
	}
	return *this;
}



//operador de pos-incremento
template<class T>
MySetIterator<T>  MySetIterator<T>::operator++(int) {
	MySetIterator<T> old(*this);
	++(*this);
	return old;
}

//operador de pos-decremento
template<class T>
MySetIterator<T>  MySetIterator<T>::operator--(int) {
	MySetIterator<T> old(*this);
	--(*this);
	return old;
}

#include <cassert>

template  <class T>
bool MySet<T>::checkIfAVL(bool printFB) const {
	int h;
	return checkIfAVL(root,h,printFB);
}


template  <class T>
bool MySet<T>::checkIfAVL(const Node<T> *root, int &altura, bool printFB) const { //verifica recursivamente se a arvore eh AVL e tambem retorna a altura (caso a arvore seja AVL!) da subarvore com raiz em root
	if(!root) {
		altura = -1; //arvore vazia tem altura -1 por definicao..
		return true;
	}
	int hLeft, hRight;
	if(!checkIfAVL(root->left,hLeft,printFB) || !checkIfAVL(root->right,hRight,printFB)) {
		return false; 
	}
	int fb = hRight-hLeft;
	assert(fb==root->fb);
	if(printFB) {
		std::cout << "FB(" << root->elem << "): " << fb << " " << root->fb << std::endl;
	}
	if(abs(fb) >=2) {
		return false;
	}

	altura = max(hLeft,hRight)+1;
	return true;
}


//funcao auxiliar...
//aumentouAltura "retorna" true iff a altura da sub-arvore aumentou apos a insercao do elemento...
template  <class T>
pair<typename MySet<T>::iterator,bool>  MySet<T>::insert(const T&elem, Node<T> * &root, bool &aumentouAltura, Node<T> *parent) { //retorna um iterador para o elemento inserido (o valor booleano sera' true se o elemento nao existia no conjunto e falso caso ele ja exista (ou seja, o novo elemento nao foi inserido) ).
	if(!root) {
		root = new Node<T>(elem);
		root->parent = parent;
		aumentouAltura = true;
		size_++;
		return make_pair(iterator(root),true);
	} else {
		if(root->elem==elem) {
			aumentouAltura = false;
			return make_pair(iterator(root),false);//igual.. --> elemento ja na arvore --> nada muda!
		} else 
			if(root->elem > elem) { //insercao a esquerda...
				bool aumentouAlturaFilhoEsquerdo; //poderia simplesmente reaproveitar a variavel aumentouAltura, mas nao vamos fazer isso para deixar o codigo mais facil de entender
				pair<typename MySet<T>::iterator,bool> insertAns = insert(elem, root->left, aumentouAlturaFilhoEsquerdo, root);	//temporariamente gravamos o resultado da insercao (para retornarmos depois de balancear...)		
				
				if(!aumentouAlturaFilhoEsquerdo) {
					aumentouAltura = false;					
				} else if(root->fb==0) { //as duas sub-arvores tinham a mesma autura... Como a da esquerda aumentou de altura --> novo fb sera -1 e minha sub-arvore tambem aumentou de altura...
					root->fb = -1;
					aumentouAltura = true;
				} else if(root->fb==1) { //a da direita era maior --> como a da esquerda aumentou --> agora equilibrou (e a altura da minha sub-arvore nao aumentou...)
					root->fb = 0;
					aumentouAltura = false;
				} else { // fb era -1 --> como a da esquerda aumentou --> virara -2 e teremos que rebalancear.... 
					//temos que verificar se desbalanceamento ocorreu por inserir na sub-arvore esquerda do filho esquerdo ou na direita do filho esquerdo (veja os diagramas para entender!)
					Node<T> *p = root; //"renomeie" a raiz para ser p (vamos usar a mesma notacao da transparencia para evitar erros). 
					Node<T> *q = root->left;

					if(q->fb==-1) { //desbalanceou ao inserir na esquerda de q --> um rotateRight corrige o problema!
						p->left  = q->right;
						if(p->left) p->left->parent = p;
						p->fb = 0;
						q->right = p;
						q->right->parent = q;
						root = q;
						root->parent = parent;
						q->fb = 0;
					} else { //desbalanceou ao inserir no filho da direito de q (que eh o filho da esquerda) --> precisamos de um rotateLeft(Q) e um rotateRight(P)
						//vamos fazer as duas rotacoes em um so passo! (veja diagramas!)
						Node<T> *r = q->right;

						p->left = r->right;
						if(p->left) p->left->parent = p;
						q->right = r->left;
						if(q->right) q->right->parent = q;
						r->left = q;
						q->parent = r;
						r->right = p;
						p->parent = r;
						
						if(r->fb==-1) {
							p->fb = 1;
							q->fb = 0;
						} else {
							p->fb = 0;
							q->fb = -1;
						}
						r->fb = 0;
						root = r;
						root->parent = parent;
					}
					aumentouAltura = 0;//a altura nao eh modificada! veja os exemplos nos slides...
				}
				return insertAns;
			}
			else { //insercao a direita... 
				bool aumentouAlturaFilhoDireito; //poderia simplesmente reaproveitar a variavel aumentouAltura, mas nao vamos fazer isso para deixar o codigo mais facil de entender
				pair<typename MySet<T>::iterator,bool> insertAns = insert(elem, root->right, aumentouAlturaFilhoDireito, root);	//temporariamente gravamos o resultado da insercao (para retornarmos depois de balancear...)		
				
				if(!aumentouAlturaFilhoDireito) {
					aumentouAltura = false;					
				} else if(root->fb==0) { //as duas sub-arvores tinham a mesma autura... Como a da direita aumentou de altura --> novo fb sera 1 e minha sub-arvore tambem aumentou de altura...
					root->fb = 1;
					aumentouAltura = true;
				} else if(root->fb==-1) { //a da esquerda era maior --> como a da direita aumentou --> agora equilibrou (e a altura da minha sub-arvore nao aumentou...)
					root->fb = 0;
					aumentouAltura = false;
				} else { // fb era +1 --> como a da direita aumentou --> virara +2 e teremos que rebalancear.... 
					//temos que verificar se desbalanceamento ocorreu por inserir na sub-arvore direita do filho direito ou na esquerda do filho direito (veja os diagramas para entender!)
					Node<T> *p = root; //"renomeie" a raiz para ser p (vamos usar a mesma notacao da transparencia para evitar erros). 
					Node<T> *q = root->right;

					if(q->fb==1) { //desbalanceou ao inserir na direita de q --> um rotateLeft corrige o problema!
						p->right  = q->left;
						if(p->right) p->right->parent = p;
						p->fb = 0;
						q->left = p;
						q->left->parent = q;
						root = q;
						root->parent = parent;
						q->fb = 0;
					} else { //desbalanceou ao inserir no filho da esquerda de q (que eh o filho da direita) --> precisamos de um rotateRight(Q) e um rotateLeft(P)
						//vamos fazer as duas rotacoes em um so passo! (veja diagramas!)
						Node<T> *r = q->left;

						p->right = r->left;
						if(p->right) p->right->parent = p;
						q->left = r->right;
						if(q->left) q->left->parent = q;
						r->right = q;
						q->parent = r;
						r->left = p;
						p->parent = r;
						
						if(r->fb==1) {
							p->fb = -1;
							q->fb = 0;
						} else {
							p->fb = 0;
							q->fb = 1;
						}
						r->fb = 0;

						root = r;
						root->parent = parent;
					}
					aumentouAltura = 0;//a altura nao eh modificada! veja os exemplos nos slides...
				}
				return insertAns;
			}
	}
}


template  <class T>
void MySet<T>::checkTree(const Node<T> *node) const { //funcao para verificar a integridade da arvore! (usada para debugging)
	if(!root) return;
	if(node == this->root) {
		assert(root->parent==NULL);
	}
	if(node->left) {
		if(node->left->elem >= node->elem) cerr << node->left->elem << " " << node->elem << endl;
		assert(node->left->elem < node->elem);
		assert(node->left->parent == node);
		checkTree(node->left);
	}
	if(node->right) {
		assert(node->right->elem > node->elem);
		assert(node->right->parent == node);
		checkTree(node->right);
	}
}

template  <class T>
void MySet<T>::checkTree() const {
	checkTree(this->root);
}


template  <class T>
typename MySet<T>::iterator MySet<T>::begin() {
	if(!root) return end();
	Node<T> *ptr = root;
	while(ptr->left) ptr = ptr->left;
	return iterator(ptr);
}


template  <class T>
MySet<T>::MySet(const MySet &other) {
	size_=0;
	root= NULL;
	*this = other; //vamos usar o operador de atribuicao..
}


template  <class T>
void MySet<T>::deleteNodes(Node<T> *root) {
	if(!root) return;
	deleteNodes(root->left);
	deleteNodes(root->right);
	delete root;
}

template  <class T>
MySet<T>::~MySet() {
	deleteNodes(root);
}


template  <class T>
Node<T> * MySet<T>::copyNodes(const Node<T> *root, Node<T> *parent) const {
	if(root==NULL) { //caso base
		return NULL;
	}
	Node<T> *  ans = new Node<T>(root->elem);
	ans->parent = parent;
	ans->left = copyNodes(root->left,ans);
	ans->right = copyNodes(root->right,ans);
	

	return ans;
}

template  <class T>
MySet<T> & MySet<T>::operator=(const MySet &other) {
	if(this==&other) return *this; //testa auto-atribuicao...
	deleteNodes(root);
	root = copyNodes(other.root,NULL);
	size_ = other.size_;
	return *this;
}


template  <class T>
int MySet<T>::size() const {
	return size_; //exercicio: como calcular o tamanho de forma dinamica? (i.e., sem armazenar o inteiro "size" na classe)
}




template  <class T>
pair<typename MySet<T>::iterator,bool> MySet<T>::insert(const T&elem) { //retorna um iterador para o elemento inserido (o valor booleano sera' true se o elemento nao existia no conjunto e falso caso ele ja exista (ou seja, o novo elemento nao foi inserido) ).
	bool aumentouAltura;
	return insert(elem,root, aumentouAltura, NULL);
}



//funcao auxiliar...
template  <class T>
typename MySet<T>::iterator MySet<T>::find(const T&elem, Node<T> *root) { //retorna um iterador para o elemento inserido (o valor booleano sera' true se o elemento nao existia no conjunto e falso caso ele ja exista (ou seja, o novo elemento nao foi inserido) ).
	if(!root) {		
		return iterator(NULL);
	} else {
		if(root->elem > elem) return find(elem, root->left);
		else if (root->elem < elem) return find(elem, root->right);
		else return iterator(root);//igual..
	}
}


template  <class T>
typename MySet<T>::iterator MySet<T>::find(const T&elem) {
	find(elem,root);
}





#include "MyQueue.h"


template  <class T>
void MySet<T>::imprimeBFS() const { //um nivel por vez..
	MyQueue<Node<T> *> q;
	MyQueue<Node<T> *> u;
	if(!root) return;
	u.push(root);

	int nivel = 0;
	while(!u.empty()) {
		q = u;
		u = MyQueue<Node<T> *>();

		cout <<  "Nivel " << nivel++ << " : ";
		while(!q.empty()) {
			Node<T> * p = q.front();
			q.pop();
			cout << p->elem << " ";
			if(p->left) u.push(p->left);  
			if(p->right) u.push(p->right);
		}
		cout << endl;
	}
	
}

/*
template  <class T>
void MySet<T>::imprimeBFS() const {
	MyQueue<Node<T> *> q;
	if(!root) return;
	q.push(root);

	while(!q.empty()) {
		Node<T> * p = q.front();
		q.pop();
		cout << p->elem << " ";
		if(p->left) q.push(p->left);  
		if(p->right) q.push(p->right);
	}
}
*/

template  <class T>
void MySet<T>::imprimeDFS_pre(const Node<T> *p) const {
	if(!p) return;
	cout << p->elem << " ";
	imprimeDFS_pre(p->left);
	imprimeDFS_pre(p->right);
} 

template  <class T>
void MySet<T>::imprimeDFS_in(const Node<T> *p) const {
	if(!p) return;	
	imprimeDFS_in(p->left);
	cout << p->elem << " ";
	imprimeDFS_in(p->right);
} 


template  <class T>
void MySet<T>::imprimeDFS_pos(const Node<T> *p) const {
	if(!p) return;
	imprimeDFS_pos(p->left);
	imprimeDFS_pos(p->right);
	cout << p->elem << " ";
} 


template  <class T>
void MySet<T>::imprimeDFS_pre() const {
	imprimeDFS_pre(root);
}

template  <class T>
void MySet<T>::imprimeDFS_in() const {
	imprimeDFS_in(root);
}

template  <class T>
void MySet<T>::imprimeDFS_pos() const {
	imprimeDFS_pos(root);
}





#endif