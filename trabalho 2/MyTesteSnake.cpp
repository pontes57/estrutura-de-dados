#include "Snake.h"
#include "Screen.h"
#include <iostream>

using namespace std;

void print(const Screen &s) {
    for (int j = 0; j < s.getWidth() + 2; j++) {
        if(j == 0 || j== s.getWidth() + 1)
            cout << "*";
        else
            cout << "-";
    }
    cout << endl;
    for (int i = 0; i < s.getHeight(); i++) {
        cout << "|";
        for (int j = 0; j < s.getWidth(); j++) {
            if (s.get(s.getHeight() - 1 - i, j) == Screen::EMPTY) cout << " ";
            else if (s.get(s.getHeight() - 1 - i, j) == Screen::SNAKE) cout << "x";
            else cout << "•";
        }
        cout << "|" << "\n";
    }
      for (int j = 0; j < s.getWidth() + 2; j++) {
        if(j == 0 || j== s.getWidth() + 1)
            cout << "*";
        else
            cout << "-";
    }
    cout << "\n\n";
}

int main() {
    int height = 6, width = 10;
    Screen screen(height, width);
    print(screen);
    Snake snake(4);
    cout<<"Snake construída\n";
    snake.draw(&screen,Screen::SNAKE);
    print(screen);
     cout<<"tamanho da snake:"<<snake.getLench()<<endl;

    cout<<"Copia!\n";
     Snake snake2 = snake;
     Screen screen2=screen;
     snake2.draw(&screen2,Screen::SNAKE);
     print(screen2);
     cout<<"tamanho da snake:"<<snake.getLench()<<endl;

    
    snake2.draw(&screen2,Screen::EMPTY);
    snake2.move(1,0,false);
    snake2.draw(&screen2,Screen::SNAKE);
    print(screen2);

    snake.draw(&screen,Screen::EMPTY);
    snake.move(1,0,false);
    snake.draw(&screen,Screen::SNAKE);
    print(screen);

    // snake.draw(screen,Screen::EMPTY);
    // snake.move(0,-1,false);
    // snake.draw(screen,Screen::SNAKE);
    // print(screen);
    // cout<<"tamanho da snake:"<<snake.getLength()<<endl;

    // snake.draw(screen,Screen::EMPTY);
    // snake.move(0,1,true);
    // snake.draw(screen,Screen::SNAKE);
    // print(screen);
    // cout<<"tamanho da snake:"<<snake.getLength()<<endl;
    
    return 0;
}