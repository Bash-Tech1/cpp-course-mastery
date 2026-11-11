#include <iostream>
#include <stdexcept>
using namespace std;
int get_max_from_array(int ar[], int n) {
    if (n < 0)
        throw invalid_argument("Array is empty");
    if (n == 0)
        return ar[0];
    return max(get_max_from_array(ar,n-1), n);
}
int main() {
    cout << get_max_from_array(nullptr,-1);
    return 0;
}
