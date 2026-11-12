#include <iostream>
#include <iomanip>
#include <string> // Added string header for safety
using namespace std;

int specialization_validation() {
    int num;
    cout << "Enter the specialization: ";
    while (true) {
        cin >> num;
        if (num > 0 and num <= 20)
            break;
        cout << "specialization value range is [1-20]: \n";
    }
    return num - 1;
}

int status_validation() {
    int status;
    while (true) {
        cout << "Enter status (0 for regular, 1 for urgent): ";
        cin >> status;
        if (status == 0 or status == 1)
            break;
        cout << "Status must be either 0 for regular or 1 for urgent\n";
    }
    return status;
}

string name_validation() {
    cin.ignore();
    string name;
    cout << "Enter name: ";
    getline(cin, name);
    return name;
}

struct Patient {
    // FIX 1: Removed function calls here. 
    // In C++, struct defaults run for EVERY object created. 
    // If you leave them here, the program asks for 100 names before the menu loads!
    string name;
    int status;
};

struct Hospital {
    Patient patients[20][5];
    
    // FIX 2: Initialized to {0}. 
    // Struct member arrays are not 0 by default; they hold garbage memory.
    int num_of_patient_at_each_spec[20] = {0}; 

    void print() {
        cout << "\nEnter ur choice: \n";
        cout << "1)Add a new patient\n";
        cout << "2)Print all patients\n";
        cout << "3)Get next patient\n";
        cout << "4)Exit\n";
    }

    void right_shift(const int spec) {
        for (int i = num_of_patient_at_each_spec[spec] - 1; i >= 0; --i) {
            // FIX 3: Shift the entire Patient object, not just the .name!
            // This is the superpower of structs: name and status move together.
            patients[spec][i + 1] = patients[spec][i]; 
        }
    }

    void left_shift(const int spec) {
        int count = num_of_patient_at_each_spec[spec];
        for (int i = 0; i < count - 1; ++i) {
            // FIX 4: Shift the whole struct.
            patients[spec][i] = patients[spec][i + 1];
        }
        // FIX 5: Clear the "ghost" patient by assigning a brand new, empty Patient object.
        patients[spec][count - 1] = Patient(); 
    }

    void add_new_patient() {
        int specialization = specialization_validation();
        
        if (num_of_patient_at_each_spec[specialization] == 5) {
            cout << "There is no room for patients in specialization number: " << specialization + 1 << "\n";
            return;
        }

        // FIX 6: Order of Operations (UX). 
        // We only create the Patient and ask for input AFTER we know there is room.
        Patient p;
        p.name = name_validation();
        p.status = status_validation();

        if (p.status == 1) {
            right_shift(specialization);
            // FIX 7: Assign the whole struct. No need for .name or .status.
            patients[specialization][0] = p;
        }
        else {
            patients[specialization][num_of_patient_at_each_spec[specialization]] = p;
        }
        num_of_patient_at_each_spec[specialization]++;
    }

    void get_next_patient() {
        const int specialization = specialization_validation();
        
        // FIX 8: Logic Bug. We check if the queue is 0 (empty), not 5 (full).
        if (num_of_patient_at_each_spec[specialization] == 0) {
            cout << "No patients at the moment. Have rest, Dr\n";
            return;
        }
        
        // FIX 9: No need to manually clear patients[spec][0]. 
        // left_shift naturally overwrites it, and clears the ghost at the end!
        left_shift(specialization);
        num_of_patient_at_each_spec[specialization]--;
    }

    void print_all_patients() {
        bool has_patients = false;

        for (int i = 0; i < 20; ++i) {
            if (num_of_patient_at_each_spec[i] > 0) {
                has_patients = true;
                break;
            }
        }

        if (!has_patients) {
            cout << "\nNo patients are currently waiting in any specialization.\n";
            return;
        }

        cout << "\n========================================================\n";
        cout << left << setw(6)  << "Spec"
             << "| " << setw(7) << "Count"
             << "| " << "Waiting Line" << "\n";
        cout << "========================================================\n";

        for (int i = 0; i < 20; ++i) {
            const int size = num_of_patient_at_each_spec[i];
            if (size != 0) {
                cout << left << setw(6) << i + 1
                     << "| " << setw(7) << size
                     << "| ";

                for (int j = 0; j < size; ++j) {
                    cout << patients[i][j].name;
                    if (j < size - 1) cout << ", "; 
                }
                cout << "\n";
            }
        }
        cout << "========================================================\n";
    }

    void run() {
        while (true) {
            print();
            int command; cin >> command;
            switch(command) {
                case 1: add_new_patient(); break;
                case 2: print_all_patients(); break;
                case 3: get_next_patient(); break;
                case 4: cout << "Thanks for using our hospital system!\n"; return;
                default:
                    cout << "Invalid choice. Please enter 1-4. \n";
                    break;
            }
        }
    }
};

int main() {
    Hospital hospital;
    hospital.run();
    return 0;
}