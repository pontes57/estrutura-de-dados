#include <iostream>
#include "MySet.h"

using namespace std;

int main(){
    MySet<int> arvore;
    char letra;
    int n;
    while (cin>>letra>>n){
        auto it=arvore.find(n);
        if(letra=='C'){
            if (it==NULL){
                arvore.insert(n);
            }
        }
        if(letra=='S'){
            if (it!=NULL){
                it++;
                if (it!=NULL){
                    cout << *it << "\n";
                }
                else cout << "FALHA" << "\n";
            }
            else cout << "FALHA" << "\n";
        }
    }
    
}