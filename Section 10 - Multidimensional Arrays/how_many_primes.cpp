// Problem #1: How many primes
// ● Read 2 integers N and M, then Read matrix NxM.
// ● Then read integer Q, for Q queries.
// ● For each query read 4 integers: i j r c
// ○ Represents a grid (submatrix): top left (i, j) and (r, c) for (# rows, # cols)
// ● For each query, print how many prime numbers in the requested grid.
// ○ Each query should be answered using nested loops maximum not more
// ○ In future: with smart precomputation it can be done without loops
// ■ It is called Image integral in Computer Vision field.
#include <bits/stdc++.h>
using namespace std;
vector<bool> primes(100000 + 1, true);
void sieve(int n) {
        primes[0] = primes[1] = false;
        for (int p = 2; p * p <= n; p++){
            if (primes[p]) {
                for (int i = p*p; i <= n; i += p) {
                    primes[i] = false;
                }
            }
    }

}
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
    int how_many_primes(int r,int c,int rl,int cl) {
        int count = 0;
        for (int i = r; i < rl + r; ++i) {
            for (int j = c; j < cl + c; ++j) {
                count += primes[ar[i][j]];
            }
        }
        return count;
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
    sieve(100000);
    cout << "Enter the number of rows and columns: \n";
    int n, m; cin >> n >> m;
    Matrix matrix(n,m);
    int q; cin >> q;
    while (q--) {
        int l1,r1,l2,r2; cin >> l1 >> r1 >> l2 >> r2;
        l1--,r1--;
        cout << matrix.how_many_primes(l1,r1,l2,r2) << endl;
    }
    return 0;
}