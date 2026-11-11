#include <iostream>
#include <stdexcept>
using namespace std;
void right_max(int ar[], int last_index) {
    if (last_index == 0) return;
    ar[last_index - 1] = max(ar[last_index], ar[last_index - 1]);
    right_max(ar, last_index - 1);
}
void right_max_tested(int ar[], int last_index) {
    if (last_index < 0)
        throw invalid_argument("Empty Array!");
    right_max(ar, last_index);
}
void print_array(int ar[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << ar[i] << " ";
    }
    cout << endl;
}
int main() {
    int ar[] = {1,3,5,7,4,2};
    right_max_tested(ar, 5);
    print_array(ar, 6);
    return 0;
}
