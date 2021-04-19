#ifndef SCREEN_H__
#define SCREEN_H__

#include <iostream>

class Screen {
public:
    static const int FOOD=0,SNAKE=1,EMPTY=2,WALL=3;
    Screen(int,int);
    int getHeight()const {return altura;}
    int getWidth()const {return largura;}
    int get (int,int)const;
    void set(int,int,int);
    void newvec (int l);//ele ve se a coluna ta vazia e apaga ela se for
   ~Screen();//apagar a alocação dinamica
    Screen (const Screen &);
    Screen & operator =(const Screen &);
private:
    int largura,altura;
    int **data;
    int *dataHeight;
};
#endif