// Max of 6 numbers
// ● Write a function that reads 6 numbers and compute their maximum. Create
// the following functions
// ○ max(int a, int b, int c)
// ○ max(int a, int b, int c, int d)
// ○ max(int a, int b, int c, int d, int e)
// ○ max(int a, int b, int c, int d, int e, int f)
// ● How can
// ○ max(int a, int b, int c, int d) utilize max(int a, int b, int c) ? and so on

#include <iostream>
using namespace std;

int max(int a, int b){return a >= b?a:b;}
int max(int a, int b, int c){return max(max(a,b),c);}
int max(int a, int b, int c, int d){return max(max(a,b,c),d);}
int max(int a, int b, int c, int d, int e){return max(max(a,b, c, d),e);}
int max(int a, int b, int c, int d, int e, int f){return max(max(a,b, c, d, e),f);}

int main() {
    int ar[6];
    cout << "Enter 6 numbers: ";
    for (int & i : ar) cin >> i;
    cout << "The maximum is: " << max(ar[0],ar[1],ar[2],ar[3],ar[4],ar[5]);
    return 0;
}
