#include <iostream>
using namespace std;
const int SIZE = 100;
struct Queue {
    int ar[SIZE] = {};
    int current_index = 0;
    bool array_is_full() const{return current_index >= SIZE - 1;}
    void array_full_checker() const { if (array_is_full()) throw invalid_argument("Array is full");}
    void right_shift() {
        array_full_checker();
        for (int i = current_index - 1; i >= 0; --i) {
            ar[i + 1] = ar[i];
        }
    }
    void left_shift() {
        array_full_checker();
        for (int i = 0; i <= current_index - 1; ++i) {
            ar[i] = ar[i + 1];
        }
    }
    void add_end(const int value) {
        array_full_checker();
        ar[current_index++] = value;
    }
    void add_front(const int value) {
        right_shift();
        ar[0] = value;
        current_index++;
    }
    int remove_front() {
        const int temp = ar[0];
        left_shift();
        current_index--;
        return temp;
    }
    void print() {
        cout << "Array current capacity is: " << current_index << "\nElements are: ";
        for (int i = 0; i < current_index; ++i) {
            cout << ar[i] << " ";
        }
        cout << endl;
    }
};
int main() {
    Queue queue;
    queue.add_front(12);
    queue.print();
    queue.add_front(13);
    queue.print();
    queue.add_end(100);
    queue.print();
    queue.remove_front();
    queue.print();
    return 0;
}
