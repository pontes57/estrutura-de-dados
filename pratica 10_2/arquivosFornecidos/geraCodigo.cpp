#include <iostream>
#include <cstring>
#include "MyVecNewIterator.h"
#include "MyMap.h"
#include <utility>

using namespace std;
int main(int argc, char *argv[]){
    int cont = 0;
    string entrada;
    MyMap<string, int> list;
    while(cin>>entrada){
        if(list.insert(make_pair(entrada,cont)).second)
            cont++;
        cout<< entrada << " "<<list[entrada]<<"\n";

    }
    return 0;
}