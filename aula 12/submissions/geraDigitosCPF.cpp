#include "MyHashMap.h"
#include "MyVecNewIterator.h"
#include <string>
#include <iostream>

using namespace std;

void calcHash(string & s) {
    int dig = 0;

    for (int i = 0; i < s.size(); i++) {
        //cout << "k = " << (s.size() - i + 1) << endl;
        dig += ((int)s[i] - 48) * (s.size() - i + 1);
    }

    //cout << "dig: " << dig << endl;

    dig = (10 * dig) % 11;

    s.append(to_string(dig));

    dig = 0;
    for (int i = 0; i < s.size(); i++) {
        dig += ((int)s[i] - 48) * (s.size() - i + 1);
    }
    dig = (10 * dig) % 11;
    s.append(to_string(dig));
}

int main() {
    int n;
    string s;

    cin >> n;
    MyVec<string> v;

    for(; n > 0; n--) {
        cin >> s;
        v.push_back(s);
    }

    for (int i = 0; i < v.size(); i++) {
        calcHash(v[i]);
        cout << v[i][v[i].size() - 2] << v[i][v[i].size() - 1] << endl;
    }
}