#include <iostream>
#include <stdexcept>
using namespace std;
double array_sum(int ar[], int n) {
    if (n < 0)
        throw invalid_argument("Array is empty!");
    if (n == 0)
        return ar[0];
    return ar[n] + array_sum(ar,n - 1);
}
double array_avg(int ar[], int n) {
    return array_sum(ar, n - 1) / n;
}
int main() {
    int ar[] = {1,2,3,4,6};
    cout << array_avg(ar, 5);
    return 0;
}
