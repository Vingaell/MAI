#include <iostream>
#include "fun.h"

using namespace std;

int main() {
    string s;
    cin >> s;
    if (s.length() == 0) {
        cout << "true";
    } else {
        if (tutu(s)) {
            cout << "true";
        } else {
            cout << "false";
        }
    }
    return 0;
}