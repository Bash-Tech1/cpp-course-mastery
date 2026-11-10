// Replace substring
// ● Implement this function
// ● string replace_str(string input, string pattern, string to)
// ○ Constraints: Input consists only of lower cases, len(pattern) > 0, len(to) >= 0
// ● The function replaces every pattern with to and return it
// ○ Input: “aabcabaaad”, “aa”, “x” - Return: “xbcabxad”
// ○ Input: “aabcabaaad”, “aa”, “aaaa” - Return: “aaaabcabaaaaad”
// ○ Input: “aabcabaaad”, “aa”, “” - Return: “bcabad”
// ● Let your code makes use of another function:
// ○ bool starts_with(string input, string pattern, int pos);
// ○ Return true if string input has the pattern starting from pos
// ○ Input: “aabcabaaad”, “aa”, 0 ⇒ True
// ○ Input: “aabcabaaad”, “aa”, 1 ⇒ False

#include <iostream>
#include <string>
using namespace std;
bool start_with(const string& input,const string& pattern, int pos) {
    if (pos + pattern.size() > input.size())
        return false;
    for (int i = 0; i < pattern.size(); ++i,++pos) {
        if (pattern[i] != input[pos])
            return false;
    }
    return true;
}
string replace_str(const string& input,const string& pattern,const string& to) {
    string temp;
    for (int i = 0; i < input.size(); i++) {
        if (start_with(input, pattern, i)) {
            temp += to;
            i += pattern.size() - 1;
        }
        else
            temp.push_back(input[i]);
    }
    return temp;
}
int main() {
    string s = "aabcabaaad";
    cout << replace_str(s, "aa","aaaa");
    return 0;
}
