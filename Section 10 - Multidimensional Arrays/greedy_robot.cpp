// Read integers N, M, then Read matrix N x M. All values are distinct.
// A robot starts at cell (0, 0).
// Take the value in the current cell and moves.
// It can move only one step to either: Right, Bottom or the diagonal.
// It always selects the cell that has maximum value.
// Print the total value the robot collects.
#include <bits/stdc++.h>
#include <thread>
#include <chrono>
using namespace std;
struct Cell {
    int num;
    bool visited = false;
};
class Grid {
    int rows = 1000;
    int columns = 1000;
    vector<vector<Cell>> ar;
public:
    Grid(int r, int c) : rows(r), columns(c), ar(r,vector<Cell>(c)) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; j++) {
                cin >> ar[i][j].num;
            }
        }
    }
    int getRows() const {return rows;}
    int getColumns() const {return columns;}
    Cell &getCell(int r, int c){return ar[r][c];}
    bool isValid(int i, int j){return i>=0 and i < rows and j >= 0 and j < columns;}
    void print(int robot_r, int robot_c) const {
        cout << "\n--- Current Board State ---\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) cout << "----";
            cout << "-\n";
            for (int j = 0; j < columns; ++j) {
                if (i == robot_r && j == robot_c) {
                    cout << "| R ";
                } else if (ar[i][j].visited) {
                    cout << "| . ";
                } else {
                    cout << "| " << ar[i][j].num << " ";
                }
            }
            cout << "|\n";
        }
        for (int j = 0; j < columns; j++) cout << "----";
        cout << "-\n";
    }
};
class Robot {
    int r = 0;
    int c = 0;
    int total = 0;
    //                     u  d  l  r  ur  dr dl  ul
    int rows_moves[8]    {-1, 1, 0, 0, -1, 1,  1, -1};
    int columns_moves[8] { 0, 0,-1, 1,  1, 1, -1, -1};

public:
    void run(Grid& grid) {
        grid.getCell(r, c).visited = true;
        total = grid.getCell(r, c).num;
        while (true) {
            grid.print(r, c);
            cout << "Robot at (" << r << ", " << c << ") | Score: " << total << "\n";
            this_thread::sleep_for(chrono::milliseconds(2000));
            int max_val = -1e9;
            int next_r = -1, next_c = -1;

            for (int i = 0; i < 8; ++i) {
                int nr = r + rows_moves[i];
                int nc = c + columns_moves[i];

                if (grid.isValid(nr, nc)) {
                    Cell& neighbour = grid.getCell(nr, nc);
                    if (!neighbour.visited and neighbour.num > max_val) {
                        max_val = neighbour.num;
                        next_r = nr;
                        next_c = nc;
                    }
                }
            }
            if (next_c == -1 or next_r == -1) {
                cout << "\nThere is no more valid moves!\n";
                break;
            }
            r = next_r;
            c = next_c;
            grid.getCell(r, c).visited = true;
            total += grid.getCell(r, c).num;
        }
    }
};
int main() {
    int n, m;
    cout << "Enter rows and columns: ";
    cin >> n >> m;
    cout << "Enter the matrix values:\n";
    Grid gameGrid(n, m);
    Robot bot;
    bot.run(gameGrid);
    cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();
    return 0;
}