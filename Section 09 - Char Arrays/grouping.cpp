// Homework 6: Grouping
// ● Read a string, then divide it to consecutive groups of same letter. Print each
// group
// ● Input ⇒ outputs.
// ○ “111222aabbb” ⇒ 111 222 aa bbb
// ○ HHHH ⇒ HHHH

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int ar[256] = {};
    for (char c : s) {
        ar[(unsigned char)c]++;
    }
    for (int i = 0; i < 256; ++i) {
        if (ar[i]) {
            while (ar[i]--) {
                cout << char(i);
            }
            cout << " ";
        }
    }
    return 0;
}