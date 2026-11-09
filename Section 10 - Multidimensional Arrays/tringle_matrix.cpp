// Problem #2: Triangular matrix
// ● Read integer N, then Read Square matrix NxN. Then, print 2 values. The
// sum of the lower triangle matrix and the upper triangle.
// ● Input
// ○ 3
// ○ 8 16 9
// ○ 3 15 27
// ○ 14 25 29
// ● Output
// ○ 94 (8+15+29+3+25+14)
// ○ 104 (8+15+29+16+27+9)

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
};
int main() {
    cout << "Enter the number of rows and columns: \n";
    int n; cin >> n;
    Matrix matrix(n,n);
    cout << matrix.lower_tringle() << endl;
    cout << matrix.upper_tringle() << endl;
    return 0;
}