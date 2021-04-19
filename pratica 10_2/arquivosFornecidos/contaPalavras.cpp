#include <iostream>
#include <cstring>
#include "MyVecNewIterator.h"
#include "MySet.h"

using namespace std;

int main(int argc, char *argv[]){
    string argumento = argv[1];         //recebemos o tipo do argumento 

    if(argumento == "myvec"){
        MyVec<string> unic;
        string word;
        int palavras = 0;

        while(cin >> word){
            palavras++;
            bool insere = true;
            for(int i=0;i<unic.size();i++){
                if(unic[i]==word) 
                    insere = false;
            }

            if(insere) 
                unic.push_back(word);
        }

        cout << palavras << " " << unic.size() << '\n';

 
    }
    else if(argumento == "myset"){
        MySet<string> unic;
        string word;
        int palavras = 0;

        while(cin >> word){
            palavras++;
            unic.insert(word);
        }

        cout << palavras << " " << unic.size() << '\n';

    }

    return 0;
}