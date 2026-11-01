

// ### **Problem 1: Employee Program (v1)**

// Help our factory manage its employees by creating a program that does the following:

// * **Menu Display:** Keep the program running forever, displaying these choices and taking user input (1 to 4):
// * `1) Add new employee`
// * `2) Print all employees`
// * `3) Delete by age`
// * `4) Update Salary by name`


// * **Choice 1 (Add):** Ask the user to input Name, Age, Salary, and Gender letter, then save the information.
// * **Choice 2 (Print):** Print all employees (one line per employee).
// * **Choice 3 (Delete by age):** Take two values (start age and end age), find all employees where `start_age <= age <= end_age`, and remove them.
// * **Choice 4 (Update salary):** Take a name and a new salary, find the employee, and update their salary.

// ---

#include <bits/stdc++.h>
using namespace std;
struct employee {
    string name;
    double age;
    double salary;
    char gender;
private:
    bool deleted = false;
public:
    employee(string n, double a, double s, char c) {
        name = n;
        age = a;
        salary = s;
        gender = c;
    }
    void print() {
        cout << "--------------------------\n";
        cout << "Name: " << name << "\nAge: " << age << "\nSalary: " << salary <<"\nGender: " << gender << "\n";
        cout << "--------------------------\n";
    }
    bool isActive(){return !deleted;}
    void remove(){deleted = true;}
};
int main() {
    vector<employee>employees;
    while (true) {
        cout << "\nEnter ur choice\n 1) Add a new employee\n 2) Print all employee\n 3) Delete by age\n 4) Update Salary by name\n";
        char x; cin >> x;
        if (x == '1') {
            string name; double age,salary;char gender;
            cout << "Please enter the name of the employee: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);
            cout << "Please enter the age of the employee: ";
            cin >> age;
            cout << "Please enter the salary of the employee: ";
            cin >> salary;
            cout << "Please enter the gender of the employee(m/f): ";
            cin >> gender;
            employee emp1(name,age,salary,gender);
            employees.push_back(emp1);
        }
        else if (x == '2') {
            for (employee &e : employees)
                if (e.isActive())
                    e.print();
        }
        else if (x == '3') {
            bool found = false;
            cout << "Please enter the range of the ages u wanna delete\n";
            double a1,a2; cin >> a1 >> a2;
            for (employee &e: employees) {
                if (e.age>= a1 and e.age <= a2 and e.isActive()) {
                    e.remove();
                    found = true;
                    e.print();
                    cout << "Has been deleted\n";
                }
            }
            if (!found) {
                cout << "There is no employees in the range ["<< a1 <<", " << a2 <<"] of age\n";
            }
        }
        else if (x == '4') {
            bool found = false;
            cout << "Enter the name of the employee and his new salary\n";
            string name;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin ,name); double salary; cin >> salary;
            for (employee &e : employees) {
                if (name == e.name and e.isActive()) {
                    e.salary = salary;
                    found = true;
                    cout << "Salary of " << name  << " has been updated to " << salary << "\n";
                }
            }
            if (!found) {
                cout << "There is no employee named " << name;
            }
        }
    }
    return 0;
}