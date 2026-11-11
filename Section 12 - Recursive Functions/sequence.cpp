#include <iostream>
using namespace std;
void sequence(int number) {
    cout << number << " ";
    if(number == 1) 
        return;
    if (number % 2 == 0)
        sequence(number/2);
    else
        sequence(3 * number + 1);
}
int main() {
    sequence(6);
    return 0;
}
