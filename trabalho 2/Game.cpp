#include "Game.h"

Game::~Game(){//pra evitar vazamento de memoria
    delete tela;
    delete cobra;
    for (int i = 0; i < 10; i++){delete[] comida[i];}
    delete[] comida;
}

Game::Game(const Game &other){
    tam=0;//inicializo as variaveis com nada pra n dar erro na hora de deletar no operador de atribuiçao
    pos[0]=0;
    pos[1]=0;
    cobra=NULL;
    tela=NULL;
    comida=NULL;
    *this=other;//deixo o trabalho pro operador de atribuiçao
}

Game& Game::operator=(const Game &other){
    if (this==&other)return *this;//autoatribuição
    delete tela;//apagando o antigo o objeto
    delete cobra;
    if(comida!=NULL){
        for (int i = 0; i < 10; i++){
            delete[] comida[i];
        }
    }
    delete[] comida;

    tam=other.tam;//copia a variavel
    pos[0]=other.pos[0];//copia a variavel
    pos[1]=other.pos[1];//copia a variavel
    cobra=new Snake(*other.cobra);//copia o objeto snake
    tela=new Screen(*other.tela);//copia o objeto screen
    comida=new int *[10];//crio o array de comida
    for (int i = 0; i < 10; i++){//percorre o vetor de comidas
        if (other.comida[i]!=NULL){//se existir a comida
            for(int j=0;j<3;j++){
                comida[i][j]=other.comida[i][j];//eu copio as informaçoes da comida
            }
        }
    else{comida[i]=NULL;}//caso n exista da comida
    }
    return *this;
}

Game::Game(int a,int l,int t){
    tela=new Screen(a,l);//crio o objeto do tipo screen
    cobra=new Snake(t);//crio o objeto do tipo snake
    cobra->draw(tela,tela->SNAKE);//desenho a cobra
    pos[0]=0;//a posiçao da altura da cabeça da cobra
    pos[1]=t-1;//a posiçao da largura da cabeça da cobra
    comida=new int *[10];//crio o array de comida
    for (int i = 0; i < 10; i++){comida[i]=NULL;}//por enquanto nao tenho comida alguma
    tam=t;//guardo o tamanho da cobra
}

void Game::addFood(int r,int c,int ttl){
    if (tela->get(r,c)==tela->EMPTY){//so adiciono a comida se o pixel tiver vazio
        for (int i = 0; i < 10; i++){//percorro o array de comida
            if (comida[i]==NULL){//vejo se essa posição ta vazia
                comida[i]=new int[3];//crio o vetor pra guadar as informaçoes da comida
                comida[i][0]=r;//linha da comida
                comida[i][1]=c;//coluna da comida
                comida[i][2]=ttl;//tempo que a comida dura
                break;//ja guardei as informaçoes da comida entao saio
            }
        }
        tela->set(r,c,tela->FOOD);//seto a posiçao com comida
    }
}

int Game::getNumfood(){
    int cont=0;//contador
    for (int i = 0; i < 10; i++){//percorro o array
        if (comida[i]!=NULL){cont++;}//se tiver algo guardado no array dou ++
    }
    return cont;//retorno o contador
}

bool Game::step(int dr,int dc){
    int*ajuda=NULL;//pra guardar as posiçoes dos nodos da cobra que eu precisar
    if(tam!=1){//se a cobra n tiver tamanho 1
        ajuda=cobra->penultimo();//eu guardo a posição
        if (pos[0]+dr==ajuda[0] && pos[1]+dc==ajuda[1]){//verifico se estou entrando pra dentro da cobra
            if(dr!=0){dr=-1*dr;}//inverto a ordem da cobra se precisar
            else{dc=-1*dc;}//inverto a ordem da cobra se precisar
        }
        delete[] ajuda;//deleto a memoria alocada na função penultimo
        ajuda=NULL;//coloco null pra utilizar novamente no fim da funçao
    }

    gerenciacomida();//vai reduzir o tempo das comida e apagar se precisar

    if(tela->get(pos[0]+dr,pos[1]+dc)==tela->WALL || tela->get(pos[0]+dr,pos[1]+dc)==tela->SNAKE){//verifica se eu estou batendo no muro ou na cobra
        return false;//termino o jogo
    }
    
    bool eating=false;//variavel pra ver se estou comendo
    if(tela->get(pos[0]+dr,pos[1]+dc)==tela->FOOD){//vejo se irei comer uma comida
        eating=true;//se sim
    }
    if(!eating){//caso eu nao coma
        ajuda=cobra->rabo();//guardo a posição do ultimo nodo da cobra
        tela->set(ajuda[0],ajuda[1],tela->EMPTY);//apago da tela o ultimo nodo
    }

    cobra->move(dr,dc,eating);//movo a cobra
    cobra->draw(tela,tela->SNAKE);//desenho a cobra
    pos[0]=pos[0]+dr;//atualizo a posição da cabeça da cobra
    pos[1]=pos[1]+dc;//atualizo a posição da cabeça da cobra
    delete[] ajuda;//deleto a memoria alocada na função rabo
    return true;
}

void Game::gerenciacomida(){//serve pra reduzir o tempo das comida e apagar se precisar
    for (int i = 0; i < 10; i++){//percorre todo o array
        if (comida[i]!=NULL){//se tiver algo guardado na posição
            comida[i][2]--;//diminuo o tempo da comida
            if (comida[i][2]==-1){//caso o tempo ja tenhp espirado
                tela->set(comida[i][0],comida[i][1],tela->EMPTY);//coloco empty
                delete[]comida[i];//apago a memoria alocada
                comida[i]=NULL;//e coloco null pra saber q a posiçao da vazia
            }
        }  
    }
}