#include <iostream>
#include "MyList2.h"
using namespace std;

int main(){
  MyList2<char> v;
  v.push_front('a');
  cout << v << endl;  
  for(int i=1;i<10;i++) {
    v.push_front('a'+i);
  }
    cout << v << endl;
    cout << v.size() << endl;
  return 0;
}