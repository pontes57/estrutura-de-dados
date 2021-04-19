#ifndef SNAKE_H__
#define SNAKE_H__

#include <iostream>
#include "Screen.h"

class Node {
public:
	int data[2];//guarda as posiçoes
	Node *next;//ponteiro pro proximo nodo
	Node *prev;//ponteiro pro nodo anterior
	Node(int a,int l){
        data[0]=a;//guarda a altura do nodo
        data[1]=l;//guarda a largura do nodo
        next=NULL;//inicizaliza com null
        prev=NULL;//inicizaliza com null
    }
};

class Snake {
public:
    Snake (int tam);
    Snake(const Snake &);
    Snake & operator=(const Snake &);
    void draw (Screen *s,int state);
    void move(int dr,int dc,bool eating);
    int getLench();
    int *rabo();//retorna a posiçao do primeiro nodo
    int *penultimo();//retorna a posiçao do penultimo nodo
    ~Snake();//apagar a alocação dinamica
private:
    Node *dataFirst;
    Node *dataLast;
};
#endif
