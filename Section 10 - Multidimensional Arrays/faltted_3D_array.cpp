// Problem #4: Flatten 3D Array
// ● Read 3 numbers: DEPTH, ROWS, COLS the dimensions of 3D array
// ● Then read integer either 1 (convert 3D to 1D) or 2 (1D to 3D)
// ● If input was 1, then read 3 integers d, r, c then convert to position in 1D array
// ● If input was 2, then read 1 integer position, then convert to 3D array position
// ● Try to generalize if we have e.g. 6D array
// ● Input ⇒ Outputs
// ○ 3 4 5 1 1 0 0 ⇒ 20
// ○ 3 4 5 2 20 ⇒ 1 0 0
// ○ 3 4 5 1 1 1 1 ⇒ 26
// ○ 3 4 5 1 2 3 2 ⇒ 57
// ○ 3 4 5 1 2 0 0 ⇒ 40
// ○ 3 4 5 2 59 ⇒ 2 3 4
#include <bits/stdc++.h>
#define ll long long
using namespace std;
// convert N-Dimensions to 1D position
ll Nd_to_1d(const vector<ll>&dim, const vector<ll>&coordinates) {
    ll answer = 0, multiplier = 1;
    for (int i = dim.size() - 1; i >= 0; i--) {
        answer += coordinates[i] * multiplier;
        multiplier *= dim[i];
    }
    return answer;
}
vector<ll> oneD_to_ND(const vector<ll>&dim, ll value, ll multiplier){
    vector<ll> answers(dim.size());
    for (int i = 0; i < dim.size(); ++i) {
        answers[i] = value / multiplier;
        value -= answers[i] * multiplier;
        if (i < dim.size() - 1)
            multiplier /= dim[dim.size() - i - 2];
    }
    return answers;
    //another approach
    for (int i = dim.size() - 1; i >= 0; i--) {
        answers[i] = value % dim[i];
        value /= dim[i];
    }
}
int main() {
    cout << "Enter the size of the matrix\n";
    ll size, multi = 1; cin >> size;
    vector<ll>dim(size);
    cout << "Enter the values of the dimnesions\n";
    for (int i = 0; i < size; ++i) {
        cin >> dim[i];
        if (i > 0)
            multi *= dim[i];
    }
    cout << "press 1 to convert from " << size << "D to 1D\n or\npress 2 convert from 1D to " << size << "D\n";
    int command; cin >> command;
    if (command == 1) {
        vector<ll>coordinates(size);
        cout << "Enter the coordinates: ";
        for (int i = 0; i < size; ++i) {
            cin >> coordinates[i];
        }
        cout << Nd_to_1d(dim,coordinates) << endl;
    }
    else if (command == 2) {
        cout << "Enter the coordinate: ";
        ll val ; cin >> val;
        vector<ll> answer = oneD_to_ND(dim,val,multi);
        for (auto&i:answer) {
            cout << i << " ";
        }
    }
    else {
        cout << "input error\n";
    }
}