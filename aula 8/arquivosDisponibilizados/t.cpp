#include <iostream>
#include "MyList2NewIterator.h"
using namespace std;

int main() {
    MyList2<int> l1;
    for(int i=0;i<6;i++) {
    l1.push_back(i);
  }
    MyList2<int>::iterator it = l1.end();
    --it;
    cout << *it << endl;
  return 0;
}