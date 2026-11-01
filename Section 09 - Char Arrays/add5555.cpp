// Problem #3: Add 5555
// ● Read a very long string of digits (at least 6 digits), and add 5555 to it.
// ○ Don’t convert to integer, as integer has max limit for values
// ● Input ⇒ Outputs
// ○ “100000” ⇒ “105555”
// ○ “10001234” ⇒ “10006789”
// ○ “3001072” ⇒ “3006627”
// ○ “10999999999” ⇒ “11000005554”
// ○ “999999999999999999999999999999999” ⇒
// “1000000000000000000000000000005554”
#include <bits/stdc++.h>
using namespace std;
int charToint(char c) {return c - '0';}
char intTochar(int x){return x + '0';}
int main() {
    //get the first string
    string s1; cin >> s1;
    int s1Size = 0;
    for (int i = 0; s1[i] != '\0'; i++) s1Size++;
    //construct the second string with 5555 at the end
    string s2, answer;
    for (int i = 0; i < s1Size - 4; i++) s2 += '0';
    s2+="5555";
    //check of the equal length
    // cout << s1 << "\n" << s2;
    int carry = 0, digit;
    for (int i = s1Size - 1; i >= 0; i--) {
        digit = charToint(s1[i]) + charToint(s2[i]) + carry;
        if (digit > 9) {
            digit %= 10;
            carry = 1;
        }
        else {
            carry = 0;
        }
        answer.push_back(intTochar(digit));
    }
    if (carry)
        answer.push_back(intTochar(carry));
     reverse(answer.begin(), answer.end());
     cout << answer;
    return 0;
}