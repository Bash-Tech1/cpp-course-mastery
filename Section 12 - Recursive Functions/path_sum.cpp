#include <iostream>
#include <vector>
using namespace std;
bool valid_coordinates(const int rows, const int columns,const int x,const int y) {
    return x >= 0 and x < rows and y >= 0 and y < columns;
}
pair<int, int> indices_of_max_value(int ar[100][100],int rows, int columns, int i, int j) {
    vector<pair<int,pair<int,int>>> values_with_indices;
    if (valid_coordinates(rows,columns,i,j + 1))
        values_with_indices.push_back({ar[i][j + 1],{i, j+ 1}});
    if (valid_coordinates(rows, columns,i + 1, j))
        values_with_indices.push_back({ar[i + 1][j],{i + 1, j}});
    if (valid_coordinates(rows,columns,i + 1, j + 1))
        values_with_indices.push_back({ar[i + 1][j + 1],{i + 1, j + 1}});
    pair<int, int> answer = values_with_indices[0].second;
    int temp = values_with_indices[0].first;
    for (const auto &it : values_with_indices) {
        if (it.first > temp) {
            temp = it.first;
            answer = it.second;
        }
    }
    return answer;
}
int path_sum(int board[100][100], const int row, const int col, const int i, const int j, int& sum) {
    if (i == row - 1 and j == col - 1) return sum;
    pair<int, int> next_indices = indices_of_max_value(board,row, col,i,j);
    sum += board[next_indices.first][next_indices.second];

    return path_sum(board, row, col, next_indices.first, next_indices.second, sum);
}
int path_sum_wrapper(int board[100][100], const int rows, const int columns) {
    return path_sum(board, rows,columns,0,0,board[0][0]);
}
int main() {
    int rows = 3;
    int cols = 3;

    // Hardcoded test case from the problem
    int board[100][100] = {
        {1, 7, 8},
        {2, 10, 11},
        {20, 5, 9}
    };

    int total_sum = path_sum_wrapper(board, rows, cols);
    cout << "Output: " << total_sum << "\n"; // Should print 31
    return 0;
}
