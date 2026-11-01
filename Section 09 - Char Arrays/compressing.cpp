
// Problem #7: Compressing
// ● Read a string of letters and then compress each group of same letter
// ○ E.g. if the sub-string is cccc ⇒ c4
// ○ Use _ between each group
// ● Input ⇒ Outputs
// ○ ccccDDDxxxxxxxxe ⇒ c4_D3_x8_e1
// ○ xxxxxxxx ⇒ x8
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int ar[256] = {};
    for (char c : s) {
        ar[(unsigned char)c]++;
    }
    char compare = ' ';
    for (int i = 0; i < s.size(); ++i) {
        if (compare != s[i]) {
            compare = s[i];
            cout << s[i] << ar[s[i]];
            if (compare != s[s.size() -  1])
                cout << "_";
        }
    }
    return 0;
}