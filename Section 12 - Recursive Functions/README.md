# C++ Recursion: From Fundamentals to Professional Architecture

This repository documents my progression through advanced recursive algorithms in C++, focusing on memory management, call stack optimization, and professional design patterns.

## Core Design Patterns

### 1. The Wrapper Pattern
Used to maintain a clean public API while passing necessary state (like indices or divisors) to the recursive backend.
*   **Public Interface:** Takes only the parameters the end-user cares about (e.g., `is_prime(int n)`).
*   **Safety Guard:** Performs pre-checks (e.g., empty arrays, negative numbers, inputs < 2).
*   **Recursive Engine:** A hidden helper function that accepts additional state parameters (e.g., `int current_divisor`, `int index`).

### 2. Three Architectures of Recursion
*   **Pure Functional (Bottom-Up):** The recursion computes $O(1)$ logic and adds it to the result of the next call. No side effects. Math is resolved as the stack unwinds.
*   **State Container (Pass-by-Reference):** State is passed down the stack via memory reference (e.g., `int& total`). Excellent for accumulating data without disrupting the return type of the function.
*   **Top-Down Accumulator (Tail Recursion):** State is passed down by value. The calculation occurs *before* the recursive call, and the recursive call is the absolute final instruction. Enables compilers to optimize stack space from $O(N)$ to $O(1)$.

## String Handling & Memory Optimization

Handling text in recursion requires strict memory hygiene to avoid $O(N^2)$ "copying traps":
*   **The `.substr()` Trap:** Avoid using `std::string::substr()` in recursion, as it forces the heap to allocate a brand new copy of the string at every level.
*   **C-Strings (`const char*`):** Used raw character pointers to achieve $O(1)$ progression. The `pointer + 1` trick shifts the string forward instantly with zero memory overhead. 
*   **The Null Terminator Trick:** Replaced $O(N)$ `strlen()` checks with $O(1)$ base cases (`if (str[0] == '\0')`) to prevent hidden loop-inside-a-loop complexity traps.
*   **Modern C++ (`std::string_view`):** Utilized C++17 `string_view` to shrink boundaries (`remove_prefix`, `remove_suffix`) in $O(1)$ time while retaining modern class methods like `.length()`.

## Algorithmic Complexities Mastered

*   **$O(1)$ Call Stack Optimization:** Transitioned basic linear recursion into tail-recursive loops.
*   **$O(N)$ Traversal:** Safely navigated arrays and strings using pointer arithmetic and boundary tracking.
*   **$O(N \sqrt{M})$ Mathematical State:** Optimized primality testing by capping the recursive divisor search at $\sqrt{M}$.
*   **$O(2^N)$ Exponential Branching:** Analyzed the "amnesia flaw" of unoptimized branching recursion (e.g., standard Fibonacci) and the mathematical relationship between the number of calls per step and exponential time complexity.

## Implemented Algorithms
1.  **Array Mechanics:** Max element, sum, average, increment, accumulate, prefix/suffix sums.
2.  **String Analysis:** Zero-copy Palindrome checking, Prefix matching.
3.  **Mathematical Algorithms:** Power function, Primality testing (`is_prime`), Range prime counting.
4.  **2D Grid Navigation:** Matrix path-sum optimization (evaluating right, down, diagonal paths).
5.  **Branching Math:** Fibonacci sequence (analyzing $O(\phi^N)$ bounds).

## Golden Rules
1.  **Base Case First:** The base case acts as a bouncer. It must evaluate the *current* state and immediately return before doing any dangerous work (like array lookups or allocations).
2.  **Pass Primitives by Value:** `int`, `char`, and `bool` should be passed by value, not `const type&`, to avoid unnecessary pointer dereferencing.
3.  **Avoid Heap Allocation:** Never declare dynamic memory containers (like `std::vector`) inside a recursive step unless strictly necessary. Rely on tracking variables and stack memory.