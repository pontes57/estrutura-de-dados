#include <iostream>
#include "MyMatrix.h"
using namespace std;




int main() {
	int tams[] = {1,7,0,2};
    MyMatrix<int> m(4, tams, true);	
    for(int i=0,ct=1;i<m.getNumRows();i++) {
		for(int j=0;j<m.getNumCols(i);j++,ct++) {
			m.set(i,j,ct); 
		}
	}
	MyMatrix<int> m1=m;
	m.print();
	m1.print();
	m1.set(1,2,10);
	m.print();
	m1.print();
    return 0;
}