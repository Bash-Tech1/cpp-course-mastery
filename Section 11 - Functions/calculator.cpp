// Calculator
// ● Develop a function that allows user to do the following (menu options):
// ○ Add 2 numbers
// ○ Subtract 2 numbers
// ○ Multiply 2 numbers
// ○ Divide 2 numbers
// ○ End the program
// ● Consider the following functions:
// ○ Function to read 2 double numbers - by reference
// ○ 4 functions, one for each operation. Don’t divide by zero!
// ○ Function to display the menu of the 5 options - read number and return it.
// ■ User should enter number from 1 to 5. If not, display error message
// ■ If exit, end the program by printing how many operations were done

#include <iostream>
#include <string>
using namespace std;
static int operations_count = 0;
double add(double a, double b){operations_count++;return a + b;}
double subtract(double a, double b){operations_count++;return a - b;}
double multiply(double a, double b){operations_count++;return a * b;}
double divide(double a, double b) {
    if (b == 0) {
        cout << "Cant divide by zero!\n";
        return -1;
    }
    operations_count++;
    return a / b;
}
void readTwoNumbers(double& a, double& b) {
    cout << "Enter the 2 numbers: ";
    cin >> a >> b;
}
int displayMenu() {
    int command;
    cout << "\nPress 1 to add 2 numbers\n";
    cout << "      2 to subtract 2 numbers\n";
    cout << "      3 to multiply 2 numbers\n";
    cout << "      4 to divide 2 numbers\n";
    cout << "      5 to close the app\n";
    cout << "Enter choice: ";
    cin >> command;
    return command;
}
void program() {
    cout << "---Welcome to the calculator app---\n";
    while (true) {
        int choice = displayMenu();
        if (choice == 5)
            break;
        if (choice > 0 and choice < 5) {
            double x, y;
            readTwoNumbers(x,y);
            switch (choice) {
                case 1: cout <<"Result: "<< add(x, y) << "\n";break;
                case 2: cout <<"Result: "<< subtract(x, y) << "\n";break;
                case 3: cout <<"Result: "<< multiply(x, y) << "\n";break;
                case 4: cout <<"Result: "<< divide(x, y) << "\n";break;
            }
        }
        else {
            cout << "Invalid command, choose from [1, 5]\n";
        }
    }
    cout << "The number of operation u made r: " << operations_count << "\n";
}
int main() {
    program();
    return 0;
}
