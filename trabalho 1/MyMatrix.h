#ifndef MyMatrix_H__
#define MyMatrix_H__

#include <iostream>
#include <string>
using namespace std;

template<class T>
class MyMatrix {
protected:
    int size;
    int rows;
    int *tam;
    int *start;
    T**matriz;
    T*ragged;

public:
    MyMatrix & operator =(const MyMatrix &);
    const T& get(const int l,const int c)const;
    void set(const int l,const int c,const T elem);
    int getNumRows()const {return rows;}
    int getNumElems()const{return size;}
    int getNumCols(const int l)const;
    void resizeRow(const int l,const int c);
    void resizeNumRows(const int l);
    bool isRagged()const;
    void convertToRagged();
    void convertToTraditional();
    void print()const;
    MyMatrix(const int l,const int *c,const bool i);
    MyMatrix(const MyMatrix &other);
    ~MyMatrix();
};
//Complexidade do modo tradicional: O(R*C) precisamos varrer todas as R linhas e em todas C colunas fazer a igualdade
//Complexidade do modo ragged: O(R+T) varrer todas as R linhas e fazer a igualdade dos vetores start e varrer os T elementos igualando os vetores ragged
template<class T>
MyMatrix<T> & MyMatrix<T>::operator=(const MyMatrix &other){
	if(this==&other) return *this; //testando se é igual 
	if (other.isRagged()){//caso a outra matriz seja ragged essa tambem sera ragged
        if(isRagged()){//deletando a memoria caso seja ragged
            delete[] ragged;
            delete[] start;
            ragged=NULL;
            start=NULL;
        }
        else{//deletando a memoria caso seja tradicional
            for (int i = 0; i < rows; i++){ delete [] matriz[i];}
            delete [] matriz;
            delete [] tam; 
            matriz=NULL;
            tam=NULL;
        }
        rows = other.rows;//igualando o numero de linhas
        size = other.size;//igualando o numero de elementos
        start = new int [rows+1];//criando o vetor start com linhas+1 de tamanho
        for(int i=0;i<=rows;i++){start[i] = other.start[i];}//igualando os vetores start
        ragged= new T[size];//criando o vetor ragged com tamanho igual ao numero de elementos
        for(int i=0;i<size;i++){ragged[i] = other.ragged[i];}//igualando os vetores ragged
        return *this;//retorna a nova matriz depois de criada e igualada
    }
    else{//caso a outra matriz se ja tradicional
        if(isRagged()){//deletando a memoria caso seja ragged
            delete[] ragged;
            delete[] start;
            ragged=NULL;
            start=NULL;
        }
        else{//deletando a memoria caso seja tradicional
            for (int i = 0; i < rows; i++){ delete [] matriz[i];}
            delete [] matriz;
            delete [] tam;
            matriz=NULL;
            tam=NULL;
        }
        rows = other.rows;//igualando o numero de linhas
	    size = other.size;//igualando o numero de elementos
	    tam = new int [rows];//criando o vetor tam de tamanho do numero de linhas
        matriz=new T*[rows];//criando as linhas da matriz
	    for(int i=0;i<rows;i++){
            tam[i]=other.tam[i];//igualando os vetores tam
            matriz[i]=new T [tam[i]];//criando as colunas da matriz
            for (int j = 0; j < tam[i]; j++){
                matriz[i][j]=other.matriz[i][j];//igualando as colunas da matriz
            }
        }
        return *this;//retorna a nova matriz depois de criada e igualada
    }
}
//Complexidade do modo tradicional: O(R*C + R) percorre as R linhas fazendo a operacao de igualdade em C colunas,depois deleta as R linhas
//Complexidade do modo ragged: O(1) fara somente o retorno
template<class T>
void MyMatrix<T>::convertToRagged(){
    if (isRagged()){return;}//caso ela ja seja ragged nao faz nada
    start=new int [rows+1];//criando o vetor start com linhas+1 de tamanho
    ragged=new T [size];//criando o vetor ragged com tamanho igual ao numero de elementos
    int cont=0;//um contador para saber em qual posicao de ragged estamos
    for (int i = 0; i <rows ; i++){
        start[i]=cont;//inicializando o vetor start com as posicoes de cada linha
        for (int j = 0; j < tam[i]; j++){
            ragged[cont]=matriz[i][j];//transferindo os elementos de matriz para ragged
            cont++;//aumenta o contador de elementos transferidos
        }
    }
    start[rows]=cont;//inicilizando a ultima posicao de start
    for (int i = 0; i < rows; i++){ delete [] matriz[i];}//deletando as linhas de matriz
    delete [] matriz;//deletando matriz
    delete [] tam;//deletando tam
    matriz=NULL;//NULL para manter funcao isRagged funcional
    tam=NULL;//NULL para manter funcao isRagged funcional
}
//Complexidade do modo tradicional: O(1) fara somente o retorno
//Complexidade do modo ragged: O(R*C) percorre as R linhas fazendo a operacao de igualdade em C colunas
template<class T>
void MyMatrix<T>::convertToTraditional(){
    if (isRagged()==false){return;}//caso seja tradicional nao faz nada
    matriz=new T*[rows];//criando as linhas da matriz
    tam=new int [rows];//criando o vetor tam de tamanho do numero de linhas
    int cont=0;//um contador para saber em qual posicao de ragged estamos
    for (int i = 0; i <rows ; i++){
        tam[i]=start[i+1]-start[i];//inicializando o vetor tam
        matriz[i]=new T [tam[i]];//criando as colunas 
        for (int j = 0; j < start[i+1]-start[i]; j++){
            matriz[i][j]=ragged[cont];//transferindo os elementos de ragged para matriz
            cont++;//aumentar o contador de elementos transferidos
        }
    }
    delete[] ragged;//deletando ragged
    delete[] start;//deletando start
    ragged=NULL;//NULL para manter funcao isRagged funcional
    start=NULL;//NULL para manter funcao isRagged funcional
}
//Complexidade do modo tradiocional: O(R) percorre as R linhas deletando as linhas da matriz
//Complexidade do modo ragged: O(2) deleta os dois vetores
template<class T>
MyMatrix<T>::~MyMatrix(){
    if (isRagged()){
        delete[] ragged;//deletando ragged
        delete[] start;//deletando start
    }
    else{
        for (int i = 0; i < rows; i++){ delete [] matriz[i];}//deletando as linhas de matriz
        delete [] matriz;//deletando matriz
        delete [] tam;//deletando tam
    }
}
//Complexidade do modo tradicional: O(R*C) precisamos varrer todas as R linhas e em todas C colunas fazer a igualdade
//Complexidade do modo ragged: O(R+T) varrer todas as R linhas e fazer a igualdade dos vetores start e varrer os T elementos igualando os vetores ragged
template<class T>
MyMatrix<T>::MyMatrix(const MyMatrix &other){
    ragged=NULL;//os NULL servem para o delete que ocorrera no operador =
    start=NULL;
    matriz=NULL;
    tam=NULL;
    *this=other;//o operador se encarregara de fazer a copia
}

//Complexidade do modo tradicional: O(R) percorre as R linhas criando as colunas
//Complexidade do modo ragged: O(R) percorre as R linhas inicializando o vetor start e incrementando o contador
template<class T>
MyMatrix<T>::MyMatrix(const int l,const int *c,const bool i){
    rows=l;//inicializando o numero de linhas
    int contador=0;//contador de quantos elementos temos
    if (i==false){ //caso seja uma matriz tradicional
        start=NULL;//inicializando o start
        ragged=NULL;//inicializando o ragged
        tam=new int [l];//criando o vetor tam
        matriz=new T*[l];//criando as linhas da matriz
        for (int i = 0; i < l; i++){   
            contador=contador+c[i];//soma o numero de elementos anteriores mais a quantidade adicionada agora de acordo com o vetor passado
            tam[i]=c[i];//inicializando o vetor tam com o numero de colunas que a linha tera
            matriz[i]=new T [tam[i]];//criando as colunas da matriz
        }
        size=contador;//inicializa size com o numero de elementos
    }
    else{//caso seja uma matriz ragged
        tam=NULL;//inicializando o tam
        matriz=NULL;//inicializando a matriz
        start=new int [l+1];//criando o start
        for ( int i = 0; i < l; i++){   
            start[i]=contador;//inicializando o vetor start com as posicoes de cada linha
            contador=contador+c[i];//soma o numero de elementos anteriores mais a quantidade adicionada agora de acordo com o vetor passado
        }
        size=contador;//inicializa size com o numero de elementos
        start[l]=size;//inicilizando a ultima posicao de start
        ragged=new T [size];//criando o vetor ragged
    }
}

//Complexidade do modo tradicional: O(1) so da retorno
//Complexidade do modo ragged: O(1) so da retorno
template<class T>
bool MyMatrix<T>::isRagged()const{
    if (tam==NULL){//se o vetor tam nao existe entao é uma matriz ragged
        return true;
    }
    return false;//se existir entao é uma matriz tradional
}

//Complexidade do modo tradicional: O(1) so da retorno
//Complexidade do modo ragged: O(1) so da retorno
template<class T>
int MyMatrix<T>::getNumCols(const int l)const{
    if (isRagged())//caso seja ragged
    {
        return start[l+1]-start[l];//subtraio o começo da linha da frente com a dessa sabendo assim o numero de colunas
    }
    return tam[l];//retorno a posicao de tam correspondente a essa linha
}

//Complexidade do modo tradicional: O(1) so da retorno
//Complexidade do modo ragged: O(1) so da retorno
template<class T>
const T& MyMatrix<T>:: get(const int l,const int c)const{
    if (isRagged())//caso a matriz seja ragged
    {
        return ragged[start[l]+c];//pego o comeco da linha e somo o numero de colunas para encontrar a pedida
    }
    return matriz[l][c];//retorno a linha e coluna pedida
}

//Complexidade do modo tradicional: O(1) so faz a setagem
//Complexidade do modo ragged: O(1) so faz setagem
template<class T>
void MyMatrix<T>::set(const int l,const int c,const T elem){
    if (isRagged())//caso seja ragged
    {
        ragged[start[l]+c]= elem;//pego o comeco da linha e somo o numero de colunas para encontrar a posicao e faco a igualdade
        return;//termino a funcao para nao fazer a outra operacao
    }
    matriz[l][c]= elem;//faco a igualdade na linha e coluna passada
}

//Complexidade do modo tradicional: O(R*C) percorre as R linhas daindo saida nos C elementos
//Complexidade do modo ragged: O(R*C) percorre as R linhas daindo saida nos C elementos
template<class T>
void MyMatrix<T>::print()const{
    cout << "Rows: " << getNumRows() << endl;//mostro o numero de linhas
    cout << "Elems: " << getNumElems() << endl;//mostro o numero de elementos
    if (isRagged()){//caso seja ragged
        for (int i = 0; i <rows; i++){
            if(getNumCols(i)!=0)//quando a linha nao e vazia a saida e padrao
                cout << getNumCols(i)<< ": ";
            else//caso a linha seja vazia ele nao solta um espaço para o elemento
                cout << getNumCols(i)<< ":";
            for ( int j = start[i]; j < start[i+1]-1; j++){//vai ate o penultimo elemento
                cout << ragged[j] << " ";//da saida no elemento
            }
            if(getNumCols(i)!=0)//caso nao seja uma linha vazia ja que vou dar saida num elemento
                cout << ragged[start[i+1]-1];//dou saida no ultimo elemento sem o espaço no final
            cout << "\n";
        }
            
    }
    else{//caso seja uma matriz tradicional
        for (int i = 0; i < rows; i++){
            if(getNumCols(i)!=0)//quando a linha nao e vazia a saida e padrao
                cout << getNumCols(i)<< ": ";
            else
                cout << getNumCols(i)<< ":";//caso a linha seja vazia ele nao solta um espaço para o elemento
            for (int j = 0; j < getNumCols(i)-1; j++){//vai ate o penultimo elemento
                cout << matriz[i][j] << " ";//da saida no elemento
            }
            if (getNumCols(i)>0)//caso nao seja uma linha vazia ja que vou dar saida num elemento
            {
            cout << matriz[i][getNumCols(i)-1];//dou saida no ultimo elemento sem o espaço no final
            }
            cout << "\n";
        }
    }
    
    
}
//Complexidade do modo tradicional: O(C) percorre as C colunas inicializando o vetor novo
//COmplexidade do modo ragged: O(T+R) primeiro percorro o T elementos inicilizando o novo vetor ragged e depois percorro as R linhas inicializando o novo vetor start
template<class T>
void MyMatrix<T>::resizeRow(const int l,const int c){
    if (isRagged()){//caso seja ragged
       T*ragged1=new T[size+(c-getNumCols(l))];//crio o novo vetor que sera o ragged do tamanho do novo numero de elementos
       int* start1=new int [getNumRows()+1];//crio um vetor start do mesmo tamanho do anterior ja existente
        for (int i = 0; i < c+start[l] && i<start[l+1]; i++){//pecorro o vetor ragged ate o fim da antiga linha ou da nova (a que for menor)
            ragged1[i]=ragged[i];//transfiro os elementos para o novo vetor
        }
        for (int i = start[l+1]; i <c+start[l] ; i++){//irei pecorrer as colunas a mais adiocinadas (caso o novo numero de colounas seja maior que o anterior)
            ragged1[i]=T();//inicializo os elementos com o valor padrao;
        }
        int cont=start[l+1];//pego a posicao logo apos a linha acabar (na ragged original)
        for (int i = c+start[l]; i <(c+start[l]+ (start[getNumRows()]-start[l+1])); i++){//comeco no fim da nova linha e vou ate o fim do vetor
            ragged1[i]=ragged[cont];//termino de preencher o novo vetor com as outras linhas seguintes a nova
            cont++;//passo para a proxima posicao
        }
        for (int i = 0; i <= l; i++){//vou ate a posicao da nova linha
            start1[i]=start[i];//transfiro os elementos para o novo vetor
        }
        for (int i = l+1; i <=getNumRows(); i++){//começo na posicao da proxima linha da nova linha e vou ate a ultima posicao
            start1[i]=start[i]+c-getNumCols(l);//igualo o novo vetor igual a posicao do antigo mais (ou menos) a diferença de colunas entre a antiga e a nova linha
        }
        size=size+(c-getNumCols(l));//atualizo o numero de elementos com mais (ou menos) elementos
        delete [] start;//deleto o antigo start
        start=start1;//e coloco o novo no lugar
        delete [] ragged;//deleto o antigo ragged
        ragged=ragged1;//e coloco o novo no lugar
    }
    else{//caso seja uma matriz tradicional
        T*novo =new T [c];//crio um auxiliar que sera a nova linha do vetor matriz
        for (int i = 0; i < c && i<getNumCols(l); i++){//pecorro a linha ate o fim da nova ou da antiga linha (a que for menor)
            novo[i]=matriz[l][i];//transfiro os elementos para o novo vetor
        }
        for (int i = getNumCols(l); i <c ; i++){//caso a nova linha seja maior irei do fim da antiga ate o fim da nova
            novo[i]=T();//inicializo os elementos com o valor padrao;
        }
        delete [] matriz[l];//deleto a antiga linha
        matriz[l]=novo;//e coloca a nova no lugar
        size=size+(c-tam[l]);//atualizo o numero de elementos com mais (ou menos) elementos
        tam[l]=c;//atualizo o numero de colunas na linha
    } 
}
//Complexidade do modo tradicional: caso o novo numero de linhas seja menor: O(R),percorremos as R linhas igualando o novo vetor tam ao antigo e depois deletamos as linhas desnecessarias
//                                  caso o novo numero de linhas seja maior: O(R*C),percorremos as R linhas fazendo a igualdade nas C colunas
//Complexidade do modo ragged: caso o novo numero de linhas seja menor: O(R+T),percorremos as R linhas inicilizando o novo vetor start e depois percorremos os T elementos inicilizando o novo ragged
//                                  caso o novo numero de lunhas seja maior: O(R),percorremos as R linhas inicializando o novo vetor start
template<class T>
void MyMatrix<T>::resizeNumRows(const int l){
    int contador=0;//contador para o numero de elementos
    if (isRagged()==false){//caso seja uma matriz tradicional
        if (l<rows){//caso o novo numero de linhas seja menor que o atual
            int *c=new int [l];//crio o vetor que sera o novo vetor tam do tamanho do novo numero e linhas
            for (int i = 0; i < l; i++){//percorro ate o novo numero de linhas
                contador=contador+tam[i];//vou contando o numero de elementos
                c[i]=tam[i];//transfiro os elementos para o novo vetor
            }
            delete[] tam;//deleto o antigo tam
            tam=c;//e coloco no novo no lugar
            size=contador;//atualizo o numero de elementos
            for (int i = l; i < rows; i++){//começo do fim da nova matriz e vou ate o fim da antiga
                delete [] matriz[i];//deleto a linha
            }
        }
        else{//caso o novo numero de linhas seja maior q o atual
            T**matriz1=new T*[l];//crio as linhas da matriz
            int *c=new int [l];//crio o vetor que sera o novo vetor tam do tamanho do novo numero e linhas
            for (int i = 0; i < rows; i++){//vou ate o numero de linhas atuais
                c[i]=tam[i];//transfiro os elementos para o novo vetor
                matriz1[i]=new T [c[i]];//crio as colunas
                for (int j = 0; j < c[i]; j++){ //percorro as colunas da linhas
                    matriz1[i][j]=matriz[i][j];//transfiro os elementos para o novo vetor
                }
            }
            for (int i = rows; i < l; i++){//começo do antigo numero de linha e vou ate o novo
                c[i]=0;//as novas linhas nao terao nenhuma coluna
                matriz1[i]=NULL;//inicializo as novas linhas com nada
            }
            for (int i = 0; i < rows; i++){//deletando as linhas da antiga matriz
                delete [] matriz[i];
            }
            delete [] matriz;//deletando a antiga matriz
            matriz=matriz1;//e coloco a nova no lugar
            delete [] tam;//deleto o antigo tam
            tam=c;//e coloco o novo no lugar
        }
    }
    else{//caso seja ragged
        if (l<rows){//caso o novo numero de linhas seja menor que o atual
            int* start1=new int [l+1];//crio o vetor que sera o novo start do tamanho do novo numero de linhas mais 1
            T* ragged1=new T [start[l]];//crio o vetor que sera o novo ragged
            for ( int i = 0; i < l; i++){//vou ate o novo numero de linhas
                start1[i]=start[i];//transfiro os elementos
            }
            size=start[l];//atualizo o numero de elementos
            start1[l]=size;//inicializo a ultima posicao do vetor
            for (int i = 0; i < size; i++){//vou ate o novo numero de elementos
                ragged1[i]=ragged[i];//transfiro os elementos
            }
            delete [] start;//deletando o antigo start
            start=start1;//e coloco o novo no lugar
            delete [] ragged;//deletando o antigo ragged
            ragged=ragged1;//e coloco o novo no lugar
        }
        else{//caso o novo numero de linhas seja maior que o atual
            int* start1=new int [l+1];//crio o vetor que sera o novo start do tamanho do novo numero de linhas mais 1
            for ( int i = 0; i <=getNumRows(); i++){//vou ate o numero de linhas atual
                start1[i]=start[i];//transfiro os elementos
            }
            for ( int i = getNumRows()+1; i <=l; i++){ //começo do numero de linhas antigo e vou ate o atual  
                start1[i]=start[getNumRows()];//iniciliazo todos com a posicao depois da ultima ja que as linhas seram vazias
            }
            delete [] start;//deleto a antiga start
            start=start1;//e coloco a nova no lugar
        } 
        }
        
    rows=l;//atualizo o numero de linhas
}
#endif
    