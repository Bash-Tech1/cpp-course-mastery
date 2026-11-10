# C++ Functions: Learning Journey and Technical Reference

This document serves as a comprehensive reference for the concepts, exercises, and best practices covered during the C++ Functions section.

## 1. Learning Notes

*   **Function with default values:** You cannot use a parameter without a default value after a parameter that has a default value (all default arguments must be at the end of the parameter list).
*   **Function overloading:** Overloading requires different parameters (either different types or a different count). The return type is *not* considered by the compiler when distinguishing overloaded functions.
*   **Global variables:** If you do not explicitly initialize a global variable, it will automatically be initialized to `0` by default.

## 2. Core Concepts and Mental Models

### Function Composition and Overloading
*   **Concept:** Building complex behavior by calling smaller, simpler functions (composition), and defining multiple functions with the same name but different parameters (overloading).
*   **Key Lesson:** Avoid "Double Evaluation." When a function returns a value needed for a condition and a subsequent operation, do not call it twice. Pass its result directly to the next function.
    *   *Bad:* `return max2(a,b) >= c ? max2(a,b) : c;` (Evaluates `max2` twice).
    *   *Good:* `return max(max(a, b), c);` (Evaluates once, uses overloading).

### Pass-by-Reference vs. Pass-by-Value
*   **Pass-by-Value (`int a`):** Creates an independent copy of the variable. Changes inside the function do not affect the original variable. Good for cheap, fundamental types.
*   **Pass-by-Reference (`int& a`):** Passes a direct alias to the original variable. Changes inside the function modify the original variable. Essential when a function needs to update external state (e.g., `void readTwoNumbers(double& a, double& b)`).
*   **Pass-by-Const-Reference (`const string& s`):** Passes an alias for efficiency (avoids copying large objects) but prevents the function from modifying it. This also allows passing temporary literals (like `"hello"`).
    *   *Crucial Distinction:* `const string s` makes a full, brand-new copy and *then* makes it read-only, defeating the performance benefit. Always use `const string& s`.

### The `switch` Statement vs. `else if`
*   **Mental Model:** A `switch` statement is not a series of independent conditions; it is a "jump table" with entry points.
*   **Fallthrough:** Once the program jumps to a `case`, it executes all subsequent code sequentially until it hits a `break` or the end of the block, ignoring other `case` labels.
*   **Performance:** A `switch` statement creates a jump table, allowing constant-time jumping to the correct block, whereas an `else if` chain evaluates sequentially. Best for menu systems checking a single integer or character.

### Recursion and The Call Stack
*   **Concept:** A function calling itself to solve smaller instances of the same problem.
*   **State Management:** Extra parameters (like `int start = 1`) can be added to pass state forward through recursive calls.
*   **The Unwinding Trick:** The order of execution relative to the recursive call completely changes the output.
    *   Work *before* the call: Executes top-down (e.g., 5, 4, 3, 2, 1).
    *   Work *after* the call: Relies on the Call Stack to "unwind" bottom-up (e.g., 1, 2, 3, 4, 5).

