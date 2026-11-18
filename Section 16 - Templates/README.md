# C++ Function Templates & Class Templates

Generic programming in C++ replaces repetitive, type-specific code duplication with compile-time code generation. This README summarizes the concepts, syntax, edge cases, and code examples covered in Mostafa S. Ibrahim's C++ Programming lectures on **Function Templates** and **Class Templates**. Together, these two modules trace how C++ shifts from duplicating identical logic across concrete types to building reusable functions, parameterized data structures, and type-specific specializations.

To provide a quick reference across both modules, the table below maps each major topic from the lectures to its core mechanism and representative example.

| Concept | Core Mechanism | Lecture Example |
| :--- | :--- | :--- |
| **Function Templates** | Compile-time generation of functions for used types | `MyMax<Type>(Type a, Type b)` |
| **Multiple Template Parameters** | Independent type parameters with `Type1`-driven return | `sum<Type1, Type2>(Type1 a, Type2 b)` |
| **Static Variables in Templates** | Separate `static` variable per generated instantiation | `increment_me(5)` vs. `increment_me(2.4)` |
| **Function Template Specialization** | Custom implementation for a specific type via `template<>` | `multiply(string str, int factor)` |
| **Class Templates & Member Templates** | Type-independent `struct` with optional templated methods | `MyQueue<T>` and `sum_and_add<Type>` |
| **Non-Type Template Parameters** | Compile-time `const` value parameters (e.g., array size) | `MyQueue<int, 12>` |
| **Class Template Specialization** | Dedicated `struct` definition for a specific type | `Game<string>` vs. `Game<T>` |
| **Templates vs. Overloading** | Identical syntax across types vs. varying parameters and behavior | Template generation vs. overloaded functions |

---

## 1. Why Templates Exist: Eliminating Type-Driven Code Duplication

Without templates, implementing the same algorithm for multiple data types forces developers to copy and paste identical function bodies and change only the type signatures. As illustrated in the Function Templates lecture, writing `max` separately for `int` and `double` duplicates the exact same comparison logic.

```cpp
int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

double max(double a, double b) {
    if (a > b)
        return a;
    return b;
}

int main() {
    cout << max(2, 5) << "\n";       // 5
    cout << max(2.5, 5.4) << "\n";   // 5.4
```

This duplication creates severe maintenance friction as a codebase grows. The Function Templates slides highlight three immediate consequences of relying on manual copies:

* **Tedious copy-paste**: Writing identical logic repeatedly just to swap data types wastes effort and bloats code.
* **Replicated bug fixes**: Discovering a defect in one copy requires tracking down and fixing the same bug across every type-specific version.
* **Scaling breakdown**: Maintaining six or more type variants of the same function through copy-paste becomes unmanageable.

### How Compile-Time Generation Solves the Problem

Templates instruct the compiler to generate concrete function or class versions on demand at compile time. Rather than generating code for every conceivable type, the compiler instantiates versions **only** for the cases actually used in the program. For instance, when `MyMax` is called with `int`, `double`, and `char` arguments, the compiler generates three concrete functions: `int MyMax(int, int)`, `double MyMax(double, double)`, and `char MyMax(char, char)`.

While templates eliminate duplication, the Function Templates lecture flags three practical caveats to keep in mind when applying them:

* **Naming collisions**: The lecture names the function `MyMax` rather than `max` because `max` is defined internally and causes an error.
* **Implementation complexity**: In practice, templates can be complex and difficult to apply cleanly.
* **Verbose compiler diagnostics**: Template mistakes often produce error messages that are hard to understand and ugly.

With the motivation and compile-time model established, the next step is examining how the compiler deduces parameter types, combines multiple type parameters, and scopes `static` state across generated functions.

---

## 2. How Function Templates Deduce Types, Combine Parameters, and Isolate Static State

Function templates parameterize types using either the `typename` keyword (as in `MyMax`) or the `class` keyword (as in `sum`) inside `template<...>`. How the compiler deduces those types—and how it tracks `static` state across instantiations—determines whether a template call compiles cleanly and what values it produces.

### Single-Parameter Templates and Type Deduction

The `MyMax` example demonstrates both implicit type guessing and explicit template argument specification, along with two common compile-time errors (`CE`).

```cpp
// Hey compiler this is template. Use Type
template<typename Type>
Type MyMax(Type a, Type b) {
    if (a > b)
        return a;
    return b;
}

struct Employee {};

int main() {
    cout << MyMax(2, 5) << "\n";                // 5: Guessed as int
    cout << MyMax<int>(2, 5) << "\n";           // 5
    cout << MyMax<double>(2.5, 5.4) << "\n";    // 5.4
    cout << MyMax('A', 'X') << "\n";            // X

    //cout << MyMax(2, 5.4) << "\n";            // CE: Can't guess
    cout << MyMax<int>(2, 5.4) << "\n";         // 5
    cout << MyMax<double>(2, 5.4) << "\n";      // 5.4

    Employee a, b;
    //cout << MyMax<Employee>(a, b) << "\n";    // CE: can't compare
```

Walking through these calls reveals two constraints enforced by the compiler. First, when a single template parameter `Type` governs both arguments, passing mismatched types such as `MyMax(2, 5.4)` fails with a compilation error (`CE: Can't guess`) because the compiler cannot deduce a single `Type` from an `int` and a `double`; supplying `<int>` returns `5` while `<double>` returns `5.4`. Second, the instantiated type must support every operation used inside the template body—calling `MyMax<Employee>(a, b)` fails (`CE: can't compare`) because `Employee` cannot be compared with `>`.

### Multiple Template Parameters

When a function needs to accept two potentially different types, multiple parameters can be declared in the template header, as shown in the `sum` example.

```cpp
template<class Type1, class Type2>
Type1 sum(Type1 a, Type2 b) {
    Type1 r = a + b;
    return r;
}

int main() {
    cout << sum(1, 10) << "\n";                             // 11
    cout << sum(1, 10.5) << "\n";                           // 11
    cout << sum(1.2, 10.5) << "\n";                         // 11.7
    cout << sum(1.2, 10) << "\n";                           // 11.2
    cout << sum<int, int>(1.2, 10) << "\n";                 // 11
    cout << sum('A', 1) << "\n";                            // B
    cout << sum(1, 'A') << "\n";                            // 66

    //cout << sum("I am", "Mostafa") << "\n";               // CE: char*
    cout << sum(string("I am "), string("Mostafa")) << "\n"; // I amMostafa
```

Because `sum` declares its return value and intermediate variable `r` as `Type1`, the first argument's type (unless overridden explicitly with `<int, int>`) controls truncation and character formatting. Calling `sum(1, 10.5)` returns `11` because `Type1` is `int`, whereas `sum(1.2, 10)` returns `11.2` because `Type1` is `double`. Similarly, `sum('A', 1)` yields `'B'` (`char`), while reversing the arguments in `sum(1, 'A')` yields `66` (`int`). Passing raw C-string literals in `sum("I am", "Mostafa")` triggers a compilation error (`CE: char*`), whereas wrapping them as `string` objects concatenates them into `I amMostafa`.

### Static Variables Across Generated Instantiations

Because the compiler generates an independent function for each distinct template type used, any `static` local variable inside a template function is **not** shared across different type instantiations. Each generated function receives its own `static` variable, while a `global_var` remains shared across all of them.

```cpp
int global_var = 0;

template<typename T>
void increment_me(T x) {
    static int i = 0;
    cout << ++i << " " << ++global_var << "\n";
    return;
}

int main() {
    // One static variable for each generated function

    increment_me(5);    // 1 1
    increment_me(5);    // 2 2
    increment_me(5);    // 3 3

    increment_me(2.4);  // 1 4
    increment_me(2.4);  // 2 5
    increment_me(2.4);  // 3 6
```

In this trace, the first three calls instantiate `increment_me<int>` and increment its `static int i` from `1` to `3` alongside `global_var` (`1`, `2`, `3`). When `increment_me(2.4)` runs, the compiler calls the separate `increment_me<double>` instantiation, whose own `static int i` starts at `1` while the shared `global_var` continues from `4` to `6`.

While function templates handle uniform operations across types, some data types require entirely different logic—leading to template specialization.

---

## 3. Function Template Specialization: Customizing Behavior for Specific Types

A generic template assumes that one expression works uniformly across all types, yet a specific data type must sometimes be handled differently. While `+` works for both numbers and `string` objects in `add`, `multiply` fails for `string` because C++ cannot multiply a `string` by an integer using `*`. Function template specialization solves this by providing an explicit `template<>` override for `string`.

```cpp
template<class T>
T add(T a, T b) {
    return a + b;
}

template<class T>
T multiply(T a, int factor) {
    return a * factor;
}

template<>
string multiply(string str, int factor) {
    // we can't multiply strings
    string res = "";

    while (factor--)
        res += str;

    return res;
}
```

When invoked from `main()`, numeric calls use the generic `multiply` template while `string` calls dispatch to the specialized implementation.

```cpp
int main() {
    string s = "Magic";

    cout<<add(10, 4)<<"\n";         // 14
    cout<<add(s, s)<<"\n";          // MagicMagic

    cout<<multiply(10, 4)<<"\n";    // 40
    cout<<multiply(s, 4)<<"\n";     // MagicMagicMagicMagic

    return 0;
}
```

The same compile-time generation and specialization principles extend directly from standalone functions to user-defined data structures through class templates.

---

## 4. Class Templates and Non-Type Parameters: Building Generic Data Structures

Just as function templates prevent copying identical functions, **class templates** allow a `struct` (or class) to remain independent of the data type it stores. Motivated in the Class Templates lecture by the Hospital Queue problem—where needing both an `int` queue and a `string` queue would otherwise require copy-pasting the entire struct—the compiler generates distinct versions of the class template based on the used types.

### Generic Structs and Templated Member Functions

The `MyQueue` struct template stores an array of generic type `T` alongside `pos`, provides a default constructor `MyQueue()` (setting `pos = 0`) and an array-initializing constructor `MyQueue(T param_arr[], int len)`, and exposes standard member functions alongside a **templated member function** (`sum_and_add<Type>`) that introduces its own independent type parameter.

```cpp
template<typename T>
struct MyQueue {
    T arr[100];
    int pos;

    MyQueue() {     pos = 0;    }
    MyQueue(T param_arr[], int len) {
        for (int i = 0; i < len; ++i)
            arr[i] = param_arr[i];
        pos = len;
    }
    void add_front(T elem) {
        arr[pos++] = elem;
    }

    template<typename Type>
    void sum_and_add(Type a, Type b) {
        arr[pos++] = a + b;
    }

    void print() {
        for (int i = 0; i < pos; ++i)
            cout << arr[i] << " ";
        cout<<"\n";
    }
};
```

In `main()`, `MyQueue<string>` and `MyQueue<int>` instantiate separate versions of `MyQueue`. Calling `q_dob.sum_and_add<double>(2.5, 3.9)` on `MyQueue<int>` demonstrates how class-level and method-level template parameters interact: `sum_and_add` sums two `double` values (`6.4`), and assigning the result into `T arr[pos++]` (where `T` is `int`) stores `6`, producing `3 2 6`.

```cpp
int main() {
    MyQueue<string> q_str;
    q_str.add_front("mostafa");
    q_str.add_front("saad");
    q_str.print();  // mostafa saad

    MyQueue<int> q_dob;
    q_dob.add_front(3);
    q_dob.add_front(2);
    q_dob.sum_and_add<double>(2.5, 3.9);
    q_dob.print();  // 3 2 6

    return 0;
}
```

### Non-Type Template Parameters

In the initial `MyQueue` definition, the internal array size was hardcoded to `100`. Because the compiler generates the class at compile time, templates can also accept **non-type parameters**—typically used for constants and array sizes—and can even be given a default value.

```cpp
template<typename T, int SIZE>
struct MyQueue {
    T arr[SIZE];
    int pos;
```

Instantiating this parameterized struct supplies both the element type and the compile-time size, as shown with `MyQueue<int, 12>`.

```cpp
    MyQueue<int, 12> q_dob;
    q_dob.add_front(3);
    q_dob.add_front(2);
    q_dob.sum_and_add<double>(2.5, 3.9);
    q_dob.print();  // 3 2 6
```

A strict constraint governs non-type parameters: the passed argument **must** be a `const` value known at compile time (for example, it cannot be read from a user at runtime).

Just as function templates support specialization and must be distinguished from function overloading, class templates also support type-specific specialization.

---

## 5. Class Template Specialization and Choosing Templates Over Overloading

Class templates support explicit specialization in the same way function templates do, allowing a `struct` to provide a dedicated definition for a specific type while keeping a generic definition for all others. Beyond specialization, the Class Templates lecture closes by clarifying the conceptual boundary between templates and function overloading.

### Class Template Specialization

Using `template<>`, `Game<string>` overrides the generic `Game<T>` template so that `Game<int> a;` and `Game<string> b;` instantiate distinct definitions.

```cpp
template<class T>
struct Game {
};

template<>
struct Game<string> {
};

int main() {
    Game<int> a;
    Game<string> b;

    return 0;
}
```

### Function Overloading vs. Templates

Although both mechanisms let callers invoke the same name with different data types, they address distinct design needs. The table below contrasts the two approaches using the criteria established in the Class Templates lecture.

| Dimension | Templates | Function Overloading |
| :--- | :--- | :--- |
| **Syntax & Logic** | Identical syntax for different data types | Identical function name with different parameters |
| **Behavior** | Uniform logic across types (unless specialized) | Different function behavior per overload |
| **Mechanism** | Compiler generates versions based on used types | Distinct functions defined for differing parameter sets |

Choose **templates** when the underlying syntax and logic remain identical across data types—applying template specialization when a specific data type should be handled differently—and choose **function overloading** when parameter lists and underlying function behaviors differ.
