// Problem #1: Smaller row?
// ● Read integers N, M, then Read matrix NxM. Then read Q for Q queries.
// ● Each query is 2 integers: first and 2nd row indices (1-based)
// ● Compare the 2 rows and print YES if first row < 2nd for all the row values
// ● Input ⇒ Output
// ○ 3 4
// ○ 8 16 9 52
// ○ 3 15 27 6
// ○ 14 25 29 10
// ○ 3
// ○ 1 2 ⇒ NO
// ○ 2 3 ⇒ YES
// ○ 1 3 ⇒ NO

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,m; cin >> n >> m;
    int ar[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> ar[i][j];
        }
    }
    int q; cin >> q;
    bool flag;
    while (q--) {
        flag = false;
        int ind1, ind2; cin >> ind1 >> ind2;
        for (int i = 0; i < m; ++i) {
            if (ar[ind1 - 1][i] >= ar[ind2 - 1][i]) {
                flag = true;
                break;
            }
        }
        cout << (!flag?"YES\n":"NO\n");
    }
    return 0;
}