#include "Screen.h"

Screen::~Screen(){//pra evitar vazamento de memoria
    delete[] dataHeight;
    for (int i = 0; i < largura; i++){delete [] data[i];}
    delete[] data;
}

 Screen::Screen (const Screen &other){
     largura=altura=0;//inicializo as variaveis com nada pra n dar erro na hora de deletar no operador de atribuiçao
     data=NULL;
     dataHeight=NULL;
     *this=other;//deixa o trabalho
 }

Screen & Screen::operator =(const Screen &other){
    if (this==&other)return *this;//autoatribuição
    delete[] dataHeight;//deleto o antigo objeto
    for (int i = 0; i < largura; i++){delete [] data[i];}
    delete[] data;

    altura=other.altura;//guardo a altura
    largura=other.largura;//guardo a largura
    data=new int* [largura];//crio as colunas
    dataHeight=new int [largura];//crio o vetor dataHeight
    for (int i = 0; i < largura; i++){//percorre as colubas
        dataHeight[i]=other.dataHeight[i];//copia esse vetor
        data[i]=new int [dataHeight[i]];//cria as linhas
        for (int j = 0; j < dataHeight[i]; j++){//percorre as linhas
            data[i][j]=other.data[i][j];//copia a matriz data
        }
    }
    return *this; 
}
Screen::Screen(int a,int l){
    altura=a;//guardo a altura
    largura=l;//guardo a largura
    data=new int* [l];//crio as colunas
    dataHeight=new int [l];//crio o vetor dataHeight
    for (int i = 0; i < l; i++){
        data[i]=NULL;//por enquanto nao temos linhas ainda
        dataHeight[i]=0;//por enquanto nao temos linhas ainda
    }  
}

int Screen::get(int a,int l)const{
    if (l>largura-1 || a>altura-1){return WALL;}//vejo se esta fora do jogo
    if (l<0 || a<0){return WALL;}//vejo se esta fora do jogo
    if ((dataHeight[l]-1)<a){return EMPTY;}//se a posiçao n tiver sido alocada ainda entao é empty
    return data[l][a];//retorno a posiçao
}

void Screen::set(int a,int l,int val){
    if(dataHeight[l]==0){//caso o vetor nao tenho sido alocado ainda
        data[l]=new int [a+1];//crio o vetor do tamanho necessario 
        for (int i = dataHeight[l]; i <a; i++){//percorro o novo vetor
            data[l][i]=EMPTY;//preencho com empty
        }
        data[l][a]=val;//seto a posição
        dataHeight[l]=a+1;//atualizo o tamanho da coluna
    }
    else if (dataHeight[l]<(a+1)){//caso o vetor existente seja menor
        int *ajuda=new int [a+1];//aloco um novo vetor do novo tamanho
        for (int i = 0; i < dataHeight[l]; i++){//percorro o vetor antigo
            ajuda[i]=data[l][i];//transfiro as posiçoes
        }
        for (int i = dataHeight[l]; i <a; i++){//percorro o resto do vetor
            ajuda[i]=EMPTY;//coloco empty
        }
        ajuda[a]=val;//seto a posiçao
        delete [] data[l];//deleto o vetor antigo
        data[l]=ajuda;//guardo o novo vetor
        dataHeight[l]=a+1;//atualizo o novo tamanho do vetor
    }
    else{data[l][a]=val;}//seto a posiçao

    if (val==EMPTY){newvec(l);}//caso eu esteja setando empty posso ter um vetor vazio
}

void Screen::newvec(int l){//vejo se o vetor esta vazio e apago se precisar
    for (int i = dataHeight[l]-1; i >=0; i--){//percorro vetor do fim ao começo
        if (data[l][i]!=EMPTY){//verifico se tem algo
            dataHeight[l]=i+1;//se tiver esse sera o novo tamanho do vetor
            int *ajuda=new int [i+1];//crio o vetor com o novo tamanho
            for (int i = 0; i < dataHeight[l]; i++){//percorro o novo vetor
                ajuda[i]=data[l][i];//transfiro as posiçoes
            }
            delete [] data[l];//deleto o vetor antigo
            data[l]=ajuda;//guardo o novo vetor
            return;//termino a funçao
        }
    }
    dataHeight[l]=0;//se chegou aqui é pq o vetor é vazio 
    delete [] data[l];//deleto o vetor vazio
    data[l]=NULL;//coloco null pra saber q ta vazio
}