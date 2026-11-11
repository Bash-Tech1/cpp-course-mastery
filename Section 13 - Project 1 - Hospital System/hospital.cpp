#include <iostream>
#include <iomanip>
using namespace std;
string patients_names[20][5];
int num_of_patient_at_each_spec[20];
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
void print() {
    cout << "Enter ur choice: \n";
    cout << "1)Add a new patient\n";
    cout << "2)Print all patients\n";
    cout << "3)Get next patient\n";
    cout << "4)Exit\n";
}
void right_shift(const int spec) {
    for (int i = num_of_patient_at_each_spec[spec] - 1; i >= 0; --i) {
        patients_names[spec][i + 1] = patients_names[spec][i];
    }
}
void left_shift(const int spec) {
    //start shifting
    int count = num_of_patient_at_each_spec[spec];
    for (int i = 0; i < count - 1; ++i) {
        patients_names[spec][i] = patients_names[spec][i + 1];
    }
    //i forgot to delete the last one at the queue
    patients_names[spec][count - 1] = "";
}
void add_new_patient() {
    const int specialization = specialization_validation();
    cin.ignore();
    string name;
    cout << "Enter name: ";
    getline(cin, name);
    const int status = status_validation();
    if (num_of_patient_at_each_spec[specialization] == 5) {
        cout << "There is no room for patients in specialization number: " << specialization + 1;
        return;
    }
    if (status == 1) {
        right_shift(specialization);
        patients_names[specialization][0] = name;
    }
    else
        patients_names[specialization][num_of_patient_at_each_spec[specialization]] = name;
    num_of_patient_at_each_spec[specialization]++;
}
void get_next_patient() {
    const int specialization = specialization_validation();
    if (patients_names[specialization][0].empty()) {
        cout << "No patients at the moment. Have rest, Dr\n";
        return;
    }
    patients_names[specialization][0] = "";
    left_shift(specialization);
    num_of_patient_at_each_spec[specialization]--;
}
void print_all_patients() {
    bool has_patients = false;

    // First, check if the hospital is completely empty
    for (int i = 0; i < 20; ++i) {
        if (num_of_patient_at_each_spec[i] > 0) {
            has_patients = true;
            break;
        }
    }

    if (!has_patients) {
        cout << "\nNo patients are currently waiting in any specialization.\n\n";
        return;
    }

    // Print the table header
    cout << "\n========================================================\n";
    cout << left << setw(6)  << "Spec"
         << "| " << setw(7) << "Count"
         << "| " << "Waiting Line" << "\n";
    cout << "========================================================\n";

    // Print the rows
    for (int i = 0; i < 20; ++i) {
        const int size = num_of_patient_at_each_spec[i];
        if (size != 0) {
            // Print Specialization and Count with fixed widths
            cout << left << setw(6) << i + 1
                 << "| " << setw(7) << size
                 << "| ";

            // Print the names separated by commas
            for (int j = 0; j < size; ++j) {
                cout << patients_names[i][j];
                if (j < size - 1) cout << ", "; // Add comma between names, but not after the last one
            }
            cout << "\n";
        }
    }
    cout << "========================================================\n\n";
}void run() {
    while (true) {
        print();
        int command; cin >> command;
        switch(command) {
            case 1: add_new_patient();break;
            case 2: print_all_patients();break;
            case 3: get_next_patient();break;
            case 4:cout << "Thanks for using our hospital system!\n"; return;
            default:
                cout << "Invalid choice. Please enter 1-4. \n";
                break;
        }
    }
}
int main() {
    run();
    return 0;
}
