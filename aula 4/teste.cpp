#include "Conjunto2.h"
#include <iostream>


int main()
{ Conjunto<int> dc1(2);
dc1.elementos[0]=0;
dc1.elementos[1]=0;
dc1.num_elementos=2;
cout << dc1 << endl;
return 0;
}