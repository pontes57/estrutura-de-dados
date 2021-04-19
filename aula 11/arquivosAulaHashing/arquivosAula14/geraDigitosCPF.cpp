#include <iostream>
#include "string.h"

using namespace std;

int main(){
    int n,primeiro,segundo;
    char ajuda;
    cin >> n;
    int cpf[9];
    for (int i = 0; i < n; i++){
        for (int i = 0; i < 9; i++){
            cin >> ajuda;
            cpf[i]=atoi(&ajuda);
        }
        primeiro=(((cpf[0]*10+cpf[1]*9+cpf[2]*8+cpf[3]*7+cpf[4]*6+cpf[5]*5+cpf[6]*4+cpf[7]*3+cpf[8]*2)*10)%11);
        if (primeiro==10){
            primeiro=0;
        }
        cout << primeiro;

        segundo=(((cpf[0]*11+cpf[1]*10+cpf[2]*9+cpf[3]*8+cpf[4]*7+cpf[5]*6+cpf[6]*5+cpf[7]*4+cpf[8]*3+primeiro*2)*10)%11);
        cout << segundo << endl;
    }
    return 0;
}