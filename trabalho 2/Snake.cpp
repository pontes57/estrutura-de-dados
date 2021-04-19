#include "Snake.h"

Snake::Snake(const Snake &other){
    dataFirst=dataLast=NULL;
    *this=other;
}

Snake& Snake::operator=(const Snake &other){
    if (this==&other)return *this;//autoatribuição
    Node * ajuda=dataFirst;//pra percorrer o nodo
    while (ajuda!=NULL){//enquanto nao acabar os nodo
        Node *temp=ajuda->next;//eu salvo a informaçao do proximo nodo
        delete ajuda;//delete o nodo
        ajuda=temp;//e recupero a informaçao do proximo nodo
    }
    ajuda=other.dataFirst;//pra poder andar a na lista sem modifica o other
    dataFirst=dataLast=new Node (other.dataFirst->data[0],other.dataFirst->data[1]);//crio o primeiro nodo
    while (ajuda!=NULL){//enquanto a lista nao tiver acabado
        dataLast->next = new Node(ajuda->data[0],ajuda->data[1]);//crio o proximo nodo
		dataLast->next->prev = dataLast;//aviso pro proximo nodo que esse é o antecessor
		dataLast = dataLast->next;//atualizo o datalast
        ajuda=ajuda->next;
    }
    return *this;
}

Snake::~Snake(){//pra evitar vazamento de memoria
    Node * ajuda=dataFirst;//pra percorrer o nodo
    while (ajuda!=NULL){//enquanto nao acabar os nodo
        Node *temp=ajuda->next;//eu salvo a informaçao do proximo nodo
        delete ajuda;//delete o nodo
        ajuda=temp;//e recupero a informaçao do proximo nodo
    }
}

int Snake::getLench(){
    Node * ajuda=dataFirst;//pra percorrer o nodo
    int count=0;//contador
    while (ajuda!=NULL){//enquanto nao acabar os nodo
        count++;//aumento o contador
        ajuda=ajuda->next;//pego o proximo nodo
    }
    return count;//retorna o contador
}

Snake::Snake(int tam){
    dataFirst=dataLast=new Node(0,0);//crio o primeiro nodo
    for (int i = 1; i < tam; i++){
		dataLast->next = new Node(0,i);//crio o proximo nodo
		dataLast->next->prev = dataLast;//aviso pro proximo nodo que esse é o antecessor
		dataLast = dataLast->next;//atualizo o datalast
    }
    dataLast->next=NULL;//o next do datalast é sempre NULL
}

void Snake::move(int dr,int dc,bool eating){
	dataLast->next = new Node(dataLast->data[0]+dr,dataLast->data[1]+dc);//crio o nodo para o proximo pixel
	dataLast->next->prev = dataLast;////aviso pro proximo nodo que esse é o antecessor
	dataLast = dataLast->next;//atualizo o datalast que é a nova cabeça
    dataLast->next=NULL;//o next do datalast é sempre NULL
    if (!eating){//caso eu nao coma
        Node *ajuda=dataFirst;//pra poder deletar sem perder informaçao
        dataFirst=dataFirst->next;//atualizo o datafirst entao esse é o novo rabo
        dataFirst->prev=NULL;//o prev do datafirst é sempre NULL
        delete ajuda;//deleto o nodo
    }
}

void Snake::draw (Screen *s,int state){
    Node * ajuda=dataFirst;//pra percorrer o nodo
    while (ajuda!=NULL){//enquanto nao acabar os nodo
        s->set(ajuda->data[0],ajuda->data[1],state);//seta a posiçao na tela
        ajuda=ajuda->next;//vou pro proximo nodo
    }
}

int * Snake::rabo(){//retorna a posiçao do primeiro nodo
    int*ajuda=new int[2];//crio um vetor de tamanho 2
    ajuda[0]=dataFirst->data[0];//posiçao da linha
    ajuda[1]=dataFirst->data[1];//posiçao da coluna
    return ajuda;//retorno o vetor com a posiçao
}

int * Snake::penultimo(){//retorna a posiçao do penultimo nodo
    int*ajuda=new int[2];//crio um vetor de tamanho 2
    ajuda[0]=dataLast->prev->data[0];//posiçao da linha
    ajuda[1]=dataLast->prev->data[1];//posiçao da coluna
    return ajuda;//retorno o vetor com a posiçao
}