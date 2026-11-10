// Reverse a string
// ● Develop a function that do reverse for the string. Function is:
// ● string reverse_str(const string & str);
// ○ Don’t try to change str content or you will get compilation error 

#include <iostream>
#include <string>
using namespace std;
string reverse_str(const string&  s){
    string temp;
    for (int i = s.size() - 1; i >= 0; --i) temp.push_back(s[i]);
    return temp;
}

int main() {
    cout << reverse_str("Bash");
    return 0;
}

