#include <iostream>
#include<string>
#include <utility>
using namespace std;
struct Square {
    char value = ' ';
    bool is_empty() const {
        return value == ' ';
    };
};
enum class GameState {
    InProgress,
    Won,
    Draw
};
struct GameResult {
    GameState status = GameState::InProgress;
    char winner = ' ';
};
enum class MoveError {
    None,
    OutOfBound,
    Occupied
};
struct MoveResult {
    MoveError error = MoveError::None;
    GameResult game_result ;
};
class Player {
    string name;
    char value;
public:
    Player(string n, char c):name(n),value(c){}
    const string& getName() const {return name;}
    char getValue() const {return value;}
};
class Board {
    Square board[3][3];
    bool isInside(int row, int column) const  {
        return (row >= 0 and row < 3 and column >= 0 and column < 3);
    }
    bool hasWon(char player) const {
        int counter;
        //winner cases
        //rows
            for (int i = 0; i < 3; ++i) {
                counter = 0;
                for (int j = 0; j < 3; ++j) {
                    if (player == board[i][j].value and player != ' ')
                        counter++;
                }
                if (counter == 3)
                    return true;
            }
            //columns
            for (int i = 0; i < 3; ++i) {
                counter = 0;
                for (int j = 0; j < 3; ++j) {
                    if (player == board[j][i].value and player != ' ')
                        counter++;
                }
                if (counter == 3)
                    return true;
            }
            //diagonals
            if (player == ' ')
                return false;
            if (
                (player == board[0][0].value and player == board[1][1].value and player == board[2][2].value)
                or
                (player == board[0][2].value and player == board[1][1].value and player == board[2][0].value)
                )
                return true;
        return false;
    }
    bool isFull() const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j].is_empty())
                    return false;
            }
        }
        return true;
    }
public:
    char getSquare(int row, int col) const {
        return board[row][col].value;
    }
    MoveResult make_move(int row,int column, char player) {
        MoveResult move_result;
        //check the coordinates
        if (!isInside(row, column)) {
            move_result.error = MoveError::OutOfBound;
            return move_result;
        }
        //check whether the square is occupied or not
            if (!board[row][column].is_empty()) {
                move_result.error = MoveError::Occupied;
                return move_result;
            }
            //now we can make the move
            board[row][column].value = player;
            //then we need to check the game statu
            if (hasWon(player)) {
                move_result.game_result.status = GameState::Won;
                move_result.game_result.winner = player;
            }
            //Draw case
            else if (isFull())
                move_result.game_result.status = GameState::Draw;

        return move_result;
    }
};
class ConsoleUI {
public:
    Player setupPlayer(int player_num, char symbol) {
        string name;
        cout << "Enter name for Player " << player_num << " (" << symbol << "): ";
        cin >> name;
        return Player(name, symbol);
    }
    void displayBoard(const Board& board) const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; j++) {
                cout << "|" << board.getSquare(i,j);
            }
            cout << "|\n";
        }
    }
    pair<int, int> getMove(const Player &player) const {
        int row,col;
        cout << player.getName() << " (" << player.getValue() << "), enter row and column (0-2): ";
        cin >> row >> col;
        return {row, col};
    }
    void displayError(MoveError error) const {
        if (error == MoveError::OutOfBound)
            cout << "Invalid move: Coordinates out of bounds!\n";
        else if (error == MoveError::Occupied) {
            cout << "Invalid move: Square is already occupied!\n";
        }
    }
    void displayResult(const GameResult& result, const Player& p1, const Player& p2) const {
        if (result.status == GameState::Won) {
            cout << "Congratulations, ";
            if (result.winner == p1.getValue())
                cout << p1.getName();
            else
                cout << p2.getName();
            cout <<" wins!\n";
        }
        else if (result.status == GameState::Draw) {
            cout << "Its a hard-fought draw!\n";
        }
    }
};
class Game {
    Board board;
    Player p1,p2;
    ConsoleUI ui;
public:
    Game(ConsoleUI ui ,Player p1, Player p2):ui(ui),p1(p1),p2(p2) {}
    void play() {
        MoveResult move_result;
        int player_switcher = 0;
        ui.displayBoard(board);
        while (move_result.game_result.status == GameState::InProgress) {
            Player& current_player = (player_switcher % 2 == 0)?p1:p2;
            auto [row, col] = ui.getMove(current_player);
            move_result = board.make_move(row, col, current_player.getValue());
            if (move_result.error != MoveError::None) {
                ui.displayError(move_result.error);
                continue;
            }
            ui.displayBoard(board);
            if (move_result.game_result.status != GameState::InProgress)
                ui.displayResult(move_result.game_result,p1,p2);
            player_switcher++;
        }
    }
};
int main() {
    ConsoleUI ui;
    cout << "---Welcome to Tic-Tac-Toe---\n";
    Player p1 = ui.setupPlayer(1,'X');
    Player p2 = ui.setupPlayer(2,'O');
    Game game(ui,p1,p2);
    game.play();
    return 0;
}
