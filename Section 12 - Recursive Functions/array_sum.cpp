#include <iostream>
#include <stdexcept>
using namespace std;
int sum_array(int ar[], int n) {
    if (n < 0)
        throw invalid_argument("Array is empty!");
    if (n == 0)
        return ar[0];
    return ar[n] + sum_array(ar,n - 1);
}
int main() {
    int ar[] = {1,2,3,4,5};
    cout << sum_array(ar, 4);
    return 0;
}
