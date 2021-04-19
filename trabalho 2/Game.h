#ifndef GAME_H__
#define GAME_H__

#include <iostream>
#include "Screen.h"
#include "Snake.h"

class Game {
public:
    Game(const Game &);
    Game&operator=(const Game &other);
    Game(int a,int l,int t);
    Screen &getScreen(){return *tela;}
    bool step(int dr,int dc);
    void addFood(int r,int c,int ttl);
    int getNumfood();
    void gerenciacomida();//gerencia o tempo das comida e se deve apagar
    ~Game();//apagar a alocação dinamica
private:
    int tam;//guarda o tamanha da cobra
    int pos[2];//posição da cabeça
    Snake *cobra;//ponteiro pra quando eu alocar o objeto snake
    Screen *tela;//ponteiro pra quando eu alocar o objeto screen
    int **comida;//uma matriz pra guardar a comida
};
#endif