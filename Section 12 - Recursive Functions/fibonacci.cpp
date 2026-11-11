#include <iostream>
#include <stdexcept>
using namespace std;
long long fibonacci(const long long number) {
    if (number == 0 or number == 1)
        return 1;
    return fibonacci(number - 1) + fibonacci(number - 2);
}
long long fibonacci_wrapper(const long long number) {
    if (number < 0)
        throw invalid_argument("No fibonacci for negative numbers\n");
    return fibonacci(number);
}
int main() {
    cout << fibonacci_wrapper(50);
    return 0;
}
