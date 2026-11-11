#include <iostream>
#include <cmath>
using namespace std;
bool is_prime_wrapper(const int& number, const int divisor) {
    if (number < 2) return false;
    if (divisor == 1) return true;
    if (number % divisor == 0)
        return false;
    return is_prime_wrapper(number, divisor - 1);
}
bool is_prime(const int& number) {
    return is_prime_wrapper(number,static_cast<int>(sqrt(number)));
}
int count_primes(const int& start,const int& end) {
    if (start > end) return 0;
    const int temp = is_prime(start);
    return temp + count_primes(start + 1, end);
}

int main() {
    cout << count_primes(1,11);
    return 0;
}
