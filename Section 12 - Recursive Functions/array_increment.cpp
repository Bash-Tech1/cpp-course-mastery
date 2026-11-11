#include <iostream>
#include <stdexcept>
using namespace std;
void array_increment(int ar[], int n) {
    if (n < 0)
        throw invalid_argument("Array is empty!");
    ar[n]+=n;
    if (n > 0)
        array_increment(ar,n - 1);
}
void print_array(int ar[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << ar[i] << " ";
    }
    cout << endl;
}
int main() {
    int ar[] = {1,2,3,4,6};
    array_increment(ar, 4);
    print_array(ar, 5);
    return 0;
}
