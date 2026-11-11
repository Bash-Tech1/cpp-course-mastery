#include <iostream>
#include <stdexcept>
#include <cstring>
using namespace std;
bool is_prefix(const string& main, const char* prefix, const int start_pos = 0) {
    if (prefix[0] == '\0') return true;
    if (main[start_pos] != prefix[0]) return false;
    return is_prefix(main,prefix+1, start_pos + 1);
}
bool is_prefix_tested(const string& main, const char* prefix,const int start_pos = 0) {
    if (strlen(prefix) + start_pos > main.size())
        throw invalid_argument("The length of the substring is grater than the main string!");
    if (main.empty())
        throw invalid_argument("The main string is empty!");
    return is_prefix(main, prefix, start_pos);
}

int main() {
    string m = "abcdefgh";
    char* p = "abd";
    cout << is_prefix_tested(m, p, 1);
    return 0;
}
