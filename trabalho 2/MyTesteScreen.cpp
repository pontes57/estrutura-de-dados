#include "Game.h"
#include <iostream>

using namespace std;

void print(const Screen &s) {
	for(int j=0;j<s.getWidth()+2;j++) cout << "-"; 
	cout << endl;
	for(int i=0;i<s.getHeight();i++) {
		cout << "|";
		for(int j=0;j<s.getWidth();j++) {
			if(s.get(s.getHeight()-1-i,j)==Screen::EMPTY) cout << " ";
			else if(s.get(s.getHeight()-1-i,j)==Screen::SNAKE) cout << "#";
			else cout << "$";
		}
		cout << "|" << "\n";
	}
	for(int j=0;j<s.getWidth()+2;j++) cout << "-"; 
	cout << "\n\n";
}

int main() {

    int height = 6, width = 10;
    Game g(5,5,5);
    Game g1=g;
    print(g.getScreen());
    print(g1.getScreen());
    return 0;
}