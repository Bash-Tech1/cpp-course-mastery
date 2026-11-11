#include <iostream>
#include <stdexcept>
using namespace std;
int prefix_sum(int ar[],int last_index ,int len) {
  if (len <= 0)
      return 0;
    return ar[len - 1] + prefix_sum(ar, last_index, len - 1);
}
int prefix_sum_tested(int ar[],int last_index, int len) {
    if (last_index < 0)
        throw invalid_argument("Empty Array!");
    if (len > last_index + 1)
        throw invalid_argument("Length exceeds array size!");
    return prefix_sum(ar,last_index ,len);
}

int main() {
    int ar[] = {1,3,5,7,4,2};
    cout << prefix_sum_tested(ar, 5,3);
    return 0;
}
