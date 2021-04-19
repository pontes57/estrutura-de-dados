#include "Conjunto2.h"
#include <iostream>
#include <cstdlib>


int main(int argc,char *argv[]){
int tam=atoi(argv[1]);
Conjunto<double> A(tam), B(tam);
for (int i = 0; i < tam; i++)
{
    A.insere(i);
    B.insere(i);
}
Conjunto<double> C= A+B;
cout << C.pertence(10) << endl;
return 0;
}