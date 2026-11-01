// Problem #2: Compare strings
// ● Read 2 strings, then output YES if the first smaller than or equal to second.
// Otherwise, output NO
// ○ Don’t use < operator to compare strings. Use loops
// ● Input ⇒ Output
// ○ aaa aaa ⇒ YES
// ○ aaaaa aa ⇒ NO
// ○ abc d ⇒ YES
// ○ dddddddddddddd xyz ⇒ YES
// ○ azzzzzzzz za ⇒ YES
// ○ za azzzzzzzz ⇒ NO

//its not a clear question, but it means (lexicographical order), not in terms of size
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s1,s2;
    cin >> s1 >> s2;
    int s1Size = 0, s2Size = 0, minSize;
    for (int i = 0; s1[i] != '\0'; i++){s1Size++;}
    for (int i = 0; s2[i] != '\0'; i++){s2Size++;}
    (s1Size <= s2Size)?minSize = s1Size:minSize = s2Size;
    for (int i = 0; i < minSize; ++i) {
        if (s1[i] > s2[i]) {
            cout << "NO";
            return 0;
        }
        if (s1[i] < s2[i]) {
            cout << "YES";
            return 0;
        }
    }
    cout << (s1Size < s2Size?"YES":"NO");
    return 0;
}