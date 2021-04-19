#include <iostream>
using namespace std;

class Screen {
public:
    static const int FOOD=0,SNAKE=1,EMPTY=2,WALL=3;
    Screen(int,int);
    int getHeight()const {return altura;}
    int getWidth()const {return largura;}
    int get (int,int)const;
    void set(int,int,int);
    void newvec (int l);
private:
    int largura,altura;
    int **data;
    int *dataHeight;
};

Screen::Screen(int a,int l){
    altura=a;
    largura=l;
    data=new int* [l];
    dataHeight=new int [l];
    for (int i = 0; i < l; i++){
        data[i]=NULL;
        dataHeight[i]=0;
    }  
}

int Screen::get(int a,int l)const{
    if (l>largura-1 || a>altura-1){return WALL;}
    if ((dataHeight[l]-1)<a){return EMPTY;}
    return data[l][a];
}

void Screen::set(int a,int l,int val){
    if(dataHeight[l]==0){
        data[l]=new int [a+1];
        for (int i = dataHeight[l]; i <a; i++){
            data[l][i]=EMPTY;
        }
        data[l][a]=val;
        dataHeight[l]=a+1;
    }
    else if (dataHeight[l]<(a+1)){
        int *ajuda=new int [a+1];
        for (int i = 0; i < dataHeight[l]; i++){
            ajuda[i]=data[l][i];
        }
        for (int i = dataHeight[l]; i <a; i++){
            ajuda[i]=EMPTY;
        }
        ajuda[a]=val;
        delete [] data[l];
        data[l]=ajuda;
        dataHeight[l]=a+1;
    }
    else{data[l][a]=val;}

    if (val==EMPTY){newvec(l);}
}

void Screen::newvec(int l){
    for (int i = dataHeight[l]-1; i >=0; i--){
        if (data[l][i]!=EMPTY){
            dataHeight[l]=i+1;
            int *ajuda=new int [i+1];
            for (int i = 0; i < dataHeight[l]; i++){
                ajuda[i]=data[l][i];
            }
            delete [] data[l];
            data[l]=ajuda;
            return;
        }
    }
    dataHeight[l]=0;
    delete [] data[l];
}