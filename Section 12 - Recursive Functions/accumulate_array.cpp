#include <iostream>
#include <stdexcept>
using namespace std;
void accumulate_array(int ar[], int len) {
    if (len == 1)
        return ;
    accumulate_array(ar, len - 1);
    ar[len - 1] += ar[len - 2];
}
void accumulate_array_with_checks(int ar[], int len) {
    if (len < 1)
        throw invalid_argument("Array is empty!");
    accumulate_array(ar, len);
}
void print_array(int ar[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << ar[i] << " ";
    }
    cout << endl;
}
int main() {
    int ar[] = {1,2,3,4,6};
    accumulate_array_with_checks(ar, 4);
    print_array(ar, 5);
    return 0;
}
