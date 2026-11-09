# Tic-Tac-Toe --- C++ OOP Learning Project

A console-based Tic-Tac-Toe game built in C++ while learning
object-oriented programming, class responsibilities, encapsulation,
composition, and defensive programming.

The project uses a fixed **3 × 3 logical board**, two players (`X` and
`O`), and a console interface.

## Table of contents

-   [Project overview](#project-overview)
-   [How the program is organized](#how-the-program-is-organized)
-   [Class and type responsibilities](#class-and-type-responsibilities)
-   [How a move works](#how-a-move-works)
-   [Important C++ concepts learned](#important-c-concepts-learned)
-   [Design decisions and lessons](#design-decisions-and-lessons)
-   [Testing checklist](#testing-checklist)
-   [Current limitations and possible
    improvements](#current-limitations-and-possible-improvements)
-   [Building and running](#building-and-running)

## Project overview

The goal was not just to make Tic-Tac-Toe work. The goal was to practice
designing a small program in which each class has a clear responsibility
and communicates with the other classes through a simple interface.

The game supports:

-   Two named players.
-   Alternating turns: `X` and `O`.
-   A 3 × 3 board.
-   Horizontal, vertical, and diagonal win detection.
-   Draw detection.
-   Rejection of moves outside the board.
-   Rejection of moves on occupied squares.
-   Console display of the board, errors, and final result.

## How the program is organized

The main objects are composed together rather than relying on
inheritance.

``` text
main()
  |
  +-- ConsoleUI
  |     +-- Collects player names
  |     +-- Reads moves
  |     +-- Displays the board, errors, and result
  |
  +-- Player objects
  |     +-- Player 1: X
  |     +-- Player 2: O
  |
  +-- Game
        +-- Board
        +-- Player 1
        +-- Player 2
        +-- ConsoleUI
```

`Game` coordinates the game. It owns the game flow and uses `Board`,
`Player`, and `ConsoleUI` to do their respective jobs.

## Class and type responsibilities

### `Square`

Represents one cell on the board.

``` cpp
struct Square {
    char value = ' ';

    bool is_empty() const {
        return value == ' ';
    }
};
```

Key idea: **keep one source of truth**.

The cell stores only its character. Whether it is empty is derived from
`value`; we do not store a separate `bool is_empty` that could become
inconsistent with the character.

### `Player`

Stores the player's name and symbol.

``` cpp
class Player {
    string name;
    char value;

public:
    Player(string n, char c) : name(n), value(c) {}

    const string& getName() const { return name; }
    char getValue() const { return value; }
};
```

The data members are private, so other classes cannot modify them
directly.

-   `getName()` returns a `const string&`: it avoids copying the string
    and does not allow the caller to modify the player's name through
    the returned reference.
-   `getValue()` returns a `char` by value, which is inexpensive.
-   The trailing `const` on both getters means they do not modify the
    `Player` object.

The player does not store whether they are the first or second player.
That is game-flow information, so it belongs to `Game`.

### `Board`

Owns the 3 × 3 array and protects the board's state.

Its responsibilities are:

-   Check whether coordinates are inside the board.
-   Check whether a square is empty.
-   Place a player's symbol when a move is valid.
-   Detect a win.
-   Detect a full board.
-   Return the outcome of an attempted move.

Important methods:

  -----------------------------------------------------------------------
  Method                              Responsibility
  ----------------------------------- -----------------------------------
  `isInside(row, column)`             Checks that both coordinates are
                                      between 0 and 2

  `hasWon(player)`                    Checks rows, columns, and diagonals
                                      for the specified symbol

  `isFull()`                          Returns `true` only when every
                                      square is occupied

  `getSquare(row, col)`               Provides a read-only character
                                      value for displaying a cell

  `make_move(row, column, player)`    Validates and applies a move, then
                                      evaluates the result
  -----------------------------------------------------------------------

The helper methods that only inspect the board are `const`. This
communicates that they do not modify the board.

`Board` does not read from `cin` or print user-facing messages. It
reports what happened; the UI decides how to explain it.

### `ConsoleUI`

Handles console input and output.

  -----------------------------------------------------------------------
  Method                              Responsibility
  ----------------------------------- -----------------------------------
  `setupPlayer()`                     Prompts for a player's name and
                                      creates a `Player`

  `displayBoard()`                    Prints the board using the public
                                      `Board` interface

  `getMove()`                         Prompts the current player for row
                                      and column

  `displayError()`                    Explains why a move was rejected

  `displayResult()`                   Announces a win or draw
  -----------------------------------------------------------------------

`displayBoard(const Board& board) const` is an important design choice:

-   `const Board&` avoids copying the board.
-   `const` prevents this method from modifying the board through that
    parameter.
-   The UI uses `getSquare()` rather than accessing the private array
    directly.

The UI is responsible for presentation and raw input. It should not
decide whether a square is occupied or whether a move wins.

### `Game`

Coordinates the complete game.

It owns a `Board`, two `Player` objects, and a `ConsoleUI` object.

The `play()` method:

1.  Displays the initial board.
2.  Tracks whose turn it is.
3.  Asks the UI for the current player's move.
4.  Sends the move to `Board`.
5.  Displays an error and retries if the move is invalid.
6.  Displays the updated board after a valid move.
7.  Displays the final result when the game is won or drawn.
8.  Switches players after a valid move.

The current player is selected using an integer turn counter:

``` cpp
Player& current_player = (player_switcher % 2 == 0) ? p1 : p2;
```

This is simple and appropriate for a two-player game. A pointer to the
current player could also work, but it is not necessary here.

## How a move works

The `make_move()` method follows this sequence:

``` text
Receive row, column, and player symbol
                |
                v
       Are coordinates valid?
          /           \
        No             Yes
        |               |
 Return OutOfBound      v
                 Is the square empty?
                    /        \
                  No          Yes
                  |            |
          Return Occupied      v
                         Place the symbol
                               |
                               v
                         Did player win?
                           /       \
                         Yes       No
                          |         |
                        Won         v
                              Is board full?
                                /      \
                              Yes       No
                               |         |
                              Draw   InProgress
```

An invalid move returns before the board is modified. This is important:
an attempted move on an occupied square must not overwrite the existing
symbol.

The win check happens before the draw check. This matters when the ninth
move also completes a winning line: the correct result is `Won`, not
`Draw`.

## Important C++ concepts learned

### 1. Encapsulation

Keep data private and expose controlled public operations.

For example, `Board` owns its array. Other classes do not access or
modify that array directly; they use methods such as `getSquare()` and
`make_move()`.

This protects the board's invariants and reduces coupling.

### 2. Single Responsibility Principle (SRP)

A class should have one main reason to change.

In this project:

-   `Player` changes when player data or player-related behavior
    changes.
-   `Board` changes when board rules or board representation change.
-   `ConsoleUI` changes when console interaction or presentation
    changes.
-   `Game` changes when the sequence and flow of the game change.

This is why input/output was separated from board rules.

### 3. Composition

`Game` contains and coordinates other objects:

``` cpp
class Game {
    Board board;
    Player p1, p2;
    ConsoleUI ui;
};
```

This is composition: building a larger object from smaller objects with
focused responsibilities.

Inheritance is not needed just because a project uses OOP. There is no
useful parent/child relationship that needs to be modeled here.

### 4. `enum class`

Enums represent a fixed set of named states.

``` cpp
enum class GameState {
    InProgress,
    Won,
    Draw
};

enum class MoveError {
    None,
    OutOfBound,
    Occupied
};
```

`enum class` is scoped and strongly typed. It avoids treating these
values as ordinary integers and helps make comparisons explicit.

The two enums represent different concepts:

-   `GameState`: the state of the game.
-   `MoveError`: why an attempted move failed.

### 5. Result structs

Instead of returning only `true` or `false`, `make_move()` returns a
`MoveResult`:

``` cpp
struct GameResult {
    GameState status = GameState::InProgress;
    char winner = ' ';
};

struct MoveResult {
    MoveError error = MoveError::None;
    GameResult game_result;
};
```

This communicates two pieces of information:

-   Was the attempted move valid?
-   If it was valid, what is the resulting game state?

Default member initializers make the default result an
unsuccessful-error-free move with the game still in progress. The method
then changes the relevant fields when needed.

A future refinement could make invalid combinations of `GameState` and
`winner` impossible to construct, for example by using a class with
private construction and named factory functions. For this learning
project, the simple struct keeps the design easy to understand.

### 6. `const` correctness

Use `const` when a method only reads object state:

``` cpp
bool isFull() const;
bool hasWon(char player) const;
char getSquare(int row, int col) const;
```

Use a const reference when a function needs to read a potentially larger
object without copying it:

``` cpp
void displayBoard(const Board& board) const;
void displayResult(const GameResult& result,
                   const Player& p1,
                   const Player& p2) const;
```

A `const` member function promises not to modify the object through the
normal member interface.

### 7. Validation and early returns

Validate input before changing state:

``` cpp
if (!isInside(row, column)) {
    move_result.error = MoveError::OutOfBound;
    return move_result;
}

if (!board[row][column].is_empty()) {
    move_result.error = MoveError::Occupied;
    return move_result;
}
```

This is an example of **guard clauses**: handle invalid cases early,
then continue with the normal path.

It keeps the main logic less nested and prevents invalid operations from
happening.

### 8. Stream input and `cin` failure

A key distinction:

-   Entering `5` when an integer is expected is a successful extraction.
    The value is an integer, even if the application later rejects it as
    an invalid coordinate.
-   Entering `hello` when an integer is expected causes extraction to
    fail and sets the stream's failure state.

After a failed extraction, later reads also fail until the stream is
recovered. A common recovery pattern is:

``` cpp
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
```

`clear()` resets the stream's error flags. `ignore()` discards the
remaining bad input line.

The current `ConsoleUI::getMove()` does not yet implement this recovery,
so malformed non-numeric input is a known limitation.

Also, `cin >> name` reads only one word. To accept names containing
spaces, use `getline(cin >> ws, name)`.

### 9. Coordinates versus dimensions

The board is always logically 3 × 3.

A row and column are coordinates, not dimensions. They identify one
cell; they should not be used as loop limits when scanning the whole
board.

For a fixed board, loops that inspect all cells should use the actual
board bounds.

### 10. Testing edge cases

A program compiling successfully does not prove its logic is correct.

Testing should include unusual but valid situations, such as:

-   A row with two matching symbols and one different symbol.
-   Three matching corners when the center is different.
-   A win on the ninth move.
-   An occupied-square attempt followed by a valid move.
-   Negative coordinates and coordinates equal to 3.

These cases help expose false positives, stale state, and boundary
errors.

## Design decisions and lessons

### Why `Board` returns an error instead of printing one

`Board` is responsible for rules and state, not wording or console
output.

It returns a value such as `MoveError::Occupied`. `ConsoleUI` turns that
value into a message.

This means the board could later be reused by a graphical interface or a
web application without rewriting its game rules.

### Why invalid moves do not switch players

`Game` increments the turn counter only after a successful move.

An invalid attempt does not change the board, so the same player gets
another attempt.

### Why `Game` manages whether the game has ended

`Game` owns the game loop and decides when to stop asking for moves.
`Board` evaluates the board after a move.

This keeps the game lifecycle in `Game` rather than mixing it into the
board representation.

The current `Board` does not independently prevent a caller from making
a move after the game has ended. That is acceptable under the current
design because `Game` controls the lifecycle. If `Board` is later
exposed to other callers, stronger protection may be appropriate.

### Why not introduce design patterns or inheritance immediately?

Patterns are tools for solving recurring design problems, not
requirements for every OOP project.

For this game, simple classes, clear interfaces, enums, and composition
are enough. A Strategy pattern might become useful if the game later
supports different rule sets or computer-player strategies, but
introducing it now would add complexity without a real need.

## Testing checklist

Use this checklist when testing the board and full game.

  -----------------------------------------------------------------------
  Test case                           Expected behavior
  ----------------------------------- -----------------------------------
  Empty board                         `InProgress`

  Valid move                          `MoveError::None`

  Row coordinate is negative          `OutOfBound`

  Column coordinate is 3 or greater   `OutOfBound`

  Attempt to use an occupied square   `Occupied`; existing symbol remains
                                      unchanged

  Three matching symbols in a row     `Won`

  Three matching symbols in a column  `Won`

  Main diagonal completed             `Won`

  Secondary diagonal completed        `Won`

  Full board with no winning line     `Draw`

  Ninth move completes a winning line `Won`, not `Draw`

  Invalid move during a game          Same player gets another turn

  Valid move during a game            Turn switches to the other player
  -----------------------------------------------------------------------

For stronger confidence, test `Board` independently from `ConsoleUI` and
`Game`. That makes it easier to tell whether a failure comes from the
rules or from input/output and game flow.

## Current limitations and possible improvements

The submitted version is a learning milestone, not a fully hardened
production application. Possible next steps:

1.  **Handle malformed console input.** Check whether
    `cin >> row >> col` succeeds and recover from `failbit`; also handle
    end-of-file.
2.  **Accept full names.** Replace `cin >> name` with
    `getline(cin >> ws, name)`.
3.  **Validate `getSquare()` coordinates.** It currently assumes callers
    pass valid coordinates. Its current use in `displayBoard()` is safe
    because the loops pass values from 0 to 2.
4.  **Validate player symbols.** `make_move()` currently accepts any
    character. The game currently passes `X` or `O`, but the public
    method does not enforce that restriction.
5.  **Use consistent naming.** The code currently mixes `make_move`,
    `getName`, and `isFull`. Choose one convention, such as `snake_case`
    or `camelCase`, and use it consistently.
6.  **Rename `OutOfBound` to `OutOfBounds`.** This is the conventional
    English spelling.
7.  **Consider stronger result invariants.** A `GameResult` can
    currently be manually constructed with contradictory values, such as
    `Won` with no winner. A private constructor and named factory
    functions could prevent that.
8.  **Add automated tests.** Test the `Board` methods without relying on
    interactive console input.
9.  **Consider dependency injection later.** `Game` currently owns a
    concrete `ConsoleUI`. This is simple and suitable for the current
    project; an abstraction is only worth adding if the program needs
    multiple UI implementations or easier substitution in tests.
10. **Consider standard headers and namespaces.** The code uses
    `using namespace std;`. In larger projects, prefer explicit `std::`
    qualification to avoid namespace pollution.

## Building and running

The code uses C++17 features, including structured bindings:

``` cpp
auto [row, col] = ui.getMove(current_player);
```

Compile with a C++17-compatible compiler:

``` bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o tic_tac_toe
```

Run on Windows:

``` powershell
.\tic_tac_toe.exe
```

Run on Linux or macOS:

``` bash
./tic_tac_toe
```

If using CLion, select a C++17 (or newer) language standard in the CMake
configuration.

------------------------------------------------------------------------

## Closing note

This project demonstrates an important shift in how to approach
programming:

**Do not begin by asking only, "How do I make this work?" Also ask,
"Which object should be responsible for this, what should it know, and
how should it communicate with the rest of the program?"**

That question guided the evolution of this Tic-Tac-Toe
implementation---from a working game toward a more organized
object-oriented design.
