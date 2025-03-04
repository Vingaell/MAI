#include <iostream>
using namespace std;

bool tutu(string& s) {
    int count = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            count++;
        } else if (s[i] == ')') {
            count--;
        }
        if (count < 0) {
            return false;
        }
    }
    return (count == 0);
}