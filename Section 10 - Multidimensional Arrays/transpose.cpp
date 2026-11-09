// Problem #3: Transpose
// ● Read integers N, M, then Read matrix NxM. Compute another array, the
// transpose
// ● Input/output as in image

#include <bits/stdc++.h>
using namespace std;
class Matrix {
    int rows;
    int columns;
    int matrixSum = 0;
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
};
int main() {
    cout << "Enter the number of rows and columns: \n";
    int n, m; cin >> n >> m;
    Matrix matrix(n,m);
    matrix.transpose();
    return 0;
}