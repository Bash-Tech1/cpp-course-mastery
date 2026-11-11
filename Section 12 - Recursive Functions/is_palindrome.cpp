#include <iostream>
#include <stdexcept>
using namespace std;
bool is_palindrome(int ar[],int last_index) {
    if (last_index <= 0) return true;
    if (ar[0] != ar[last_index])
        return false;
    return is_palindrome(ar + 1, last_index - 2);
}
bool is_palindrome_tested(int ar[],int last_index) {
    if (last_index < 0)
        throw invalid_argument("Array is Empty!");
    return is_palindrome(ar,last_index);
}

int main() {
    int ar[] = {1,1,6,1,1};
    cout << is_palindrome_tested(ar, 4);
    return 0;
}
