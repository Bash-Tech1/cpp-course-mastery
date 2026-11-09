// Problem #2: Find mountains
// ● Read integers N, M, then Read matrix NxM. Print all positions that are
// mountain. Position is mountain if its value > 8 neighbours values
// ● Code smartly
// ● Input
// ○ 3 3
// ○ 8 6 1
// ○ 3 2 9
// ○ 1 6 4
// ● Output
// ○ 0 0 (8 > 6, 3, 2)
// ○ 1 2 (9 > 1, 2, 5, 4, 6)


#include <bits/stdc++.h>
using namespace std;
class Matrix {
    int rows;
    int columns;
    int matrixSum = 0;
    int rows_direction[8] =    {-1, 1, 0, 0, -1, 1, 1, -1};
    int columns_direction[8] = {0, 0, -1, 1, 1, 1,-1,-1};
    vector<vector<int>>ar;
public:
    Matrix(int n, int m):rows(n), columns(m),ar(n, vector<int>(m)) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> ar[i][j];
                matrixSum += ar[i][j];
            }
        }
    }
    void mountains() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                bool bigger = true;
                for (int k = 0; k < 8; k++) {
                    if (is_valid(i+rows_direction[k], j+columns_direction[k])) {
                        if (ar[i][j] <= ar[i+rows_direction[k]][j+columns_direction[k]]) {
                            bigger = false;
                            break;
                        }
                    }
                }
                if(bigger) cout <<"(" << i << ", " << j << ")\n";
            }
        }
    }
    void print() {

    }
    int lower_tringle() {
        int sum = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                sum += ar[i][j];
                if (i == j)
                    break;
            }
        }
        return sum;
    }
    int upper_tringle() {
        int sum = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = i; j < columns; ++j) {
                sum += ar[i][j];
            }
        }
        return sum;
    }
    void transpose() {
        for (int j = 0; j < columns; ++j) {
            for (int i = 0; i < rows; ++i) {
                cout << ar[i][j] << " ";
            }
            cout << "\n";
        }
    }
    bool is_valid(int i, int j) {return i >= 0 and i <  rows and j >= 0 and  j < columns;}
};
int main() {
    cout << "Enter the number of rows and columns: \n";
    int n, m; cin >> n >> m;
    Matrix matrix(n,m);
    matrix.mountains();
    return 0;
}