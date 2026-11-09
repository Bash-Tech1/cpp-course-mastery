// Problem #3: Active Robot
// ● Read integers N, M represents a matrix. A robot start at cell (0, 0).
// ● Read integer K, then K commands. Each command is 2 values
// ○ Direction from 1 to 4: up, right, down, left
// ○ Steps: a number to number steps to take in the direction. Steps [1, 1000000000]
// ○ If the robot hits the wall during the move, it circulates in the matrix.
// ○ For every command, print where is the robot now
// ● Input
// ○ 3 4 4 2 1 3 2 4 2 1 3
// ■ 2 1 means to right 1 step - 3 2 means down 2 steps
// ● Output
// ○ (0, 1) (2,1) (2, 3) (2, 3)

#include <bits/stdc++.h>
using namespace std;
class Grid {
    int rows;
    int columns;

public:
    Grid(int r, int c):rows(r),columns(c){}
    void print(int x, int y) {
        for (int i = 0; i < 2 * rows + 1; ++i) {
            if (i % 2 == 1) {
                for (int j = 0; j < columns + 1; ++j) {
                    cout << "|   ";
                    cout << (i / 2 == x and j == y ?"*":" ");
                    cout << "   ";
                }
            }
            else {
                for (int j = 0; j < columns; ++j) {
                    cout << "--------";
                }
            }
            cout << "\n";
        }

        cout << "\n";
    }
    int getRow(){return rows;}
    int getColumns(){return columns;}
};
class Robot {
    Grid grid;
    int x,y,q;
public:
    Robot(Grid grid,int x, int y ,int query):grid(grid),x(x),y(y),q(query){}

    void play() {
        grid.print(x,y);
        while (q--) {
            cout << "Enter the command\n1: up\n2 right\n3 down\n4 left  and the steps \n";
            int command, steps;cin >> command >> steps;
            int new_x = x, new_y = y;
            if (command == 1) {
                new_x = (((new_x - steps) % grid.getRow()) + grid.getRow()) % grid.getRow();
            }
            else if (command == 2) {
                new_y = (new_y + steps) % grid.getColumns();
            }
            else if (command == 3) {
                new_x = (new_x + steps) % grid.getRow();
            }
            else if (command == 4) {
                new_y = (((new_y - steps) % grid.getColumns()) + grid.getColumns()) % grid.getColumns();
            }
            grid.print(new_x, new_y);
            x = new_x;
            y = new_y;
        }
    }
};
int main() {
    cout << "Enter the dimention of the grid\n";
    int n,m,q; cin >> n >> m;
    Grid grid(n,m);
    cout << "Enter the number of queries\n";
    cin >> q;
    Robot robot(grid,0,0,q);
    robot.play();
    return 0;
}