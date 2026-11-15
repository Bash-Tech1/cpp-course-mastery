# Mistakes and Lessons Learned: Library System (Project #2)

This is a record of the questions I asked, the bugs I hit, and the review comments I got while building the [Library System](README.md). Each entry follows the same pattern: **what I asked or did → what was wrong → the fix → the takeaway**.

> Code marked ❌ is an *illustrative* example of the mistake. Code marked ✅ matches the final version in [hospital.cpp](hospital.cpp).

---

## Index

| # | Topic | Category |
| :-: | :--- | :--- |
| 1 | [Auto-increment IDs with `inline static`](#1-auto-increment-ids-with-inline-static) | C++ feature |
| 2 | [Review early, not at the end](#2-review-early-not-at-the-end) | Process |
| 3 | [Bounding loops by array size vs. record count](#3-bounding-loops-by-array-size-vs-record-count) | Performance |
| 4 | [The "empty slot" trap](#4-the-empty-slot-trap) | Memory / correctness |
| 5 | [Titles vs. copies](#5-titles-vs-copies) | Data modeling |
| 6 | [Entity ID vs. array index](#6-entity-id-vs-array-index) | Algorithms |
| 7 | [`std::sort` comparators and prefix matching](#7-stdsort-comparators-and-prefix-matching) | Compiler error / strings |
| 8 | [Const correctness](#8-const-correctness) | Compiler error |
| 9 | [Sorting the master array breaks foreign keys](#9-sorting-the-master-array-breaks-foreign-keys) | Data integrity |
| 10 | [Linker error from a `static` array size](#10-linker-error-from-a-static-array-size) | Linker error |
| 11 | [Stack overflow from a huge local object](#11-stack-overflow-from-a-huge-local-object) | Memory |
| 12 | [Mixing `cin >>` and `getline`](#12-mixing-cin--and-getline) | Input handling |

---

## 1. Auto-increment IDs with `inline static`

**My question:** *"I'm thinking of making book IDs automatic, like a database, using a static variable in the `Book` struct. What do you think?"*

**Lesson:** A `static` data member is shared by **all** objects of the struct. That makes it work like SQL's `AUTO_INCREMENT`.

```cpp
// ✅ Final version
struct Book {
    inline static int id_assigner = 0;   // C++17: declared and initialized inside the struct
    int id = 0;
    Book() {}                            // used to fill the array, does NOT use up an ID
    Book(string name, int amount) : name(name), total_quantity(amount) {
        id = id_assigner++;              // only real books get an ID
    }
};
```

- `inline static` (C++17) lets you initialize the counter inside the struct, so you don't need a separate definition in a `.cpp` file.
- **Why two constructors:** `Book books[10000]` calls the default constructor 10,000 times. If the default constructor took IDs, the first real book would get ID `10000`.

> **Takeaway:** Decide which constructor "creates a real entity" and give only that one side effects.

---

## 2. Review early, not at the end

**My question:** *"I've done about 40% of the project. Is now a good time for a review, or should I wait until I finish?"*

**Lesson:** Review **now**. Design problems (how IDs work, how data is stored) get more expensive to fix with every feature built on top of them. Several of the entries below (#4, #6, #9) were found or prevented because of this early review.

> **Takeaway:** Get the data model reviewed before you build features on top of it.

---

## 3. Bounding loops by array size vs. record count

**My question:** *"I don't see the problem with the range-based loop. It returns as soon as it finds the first match, so what's the difference?"*

**What was wrong:** A range-based `for` over a fixed array visits **every slot**, including the empty ones.

```cpp
// ❌ Goes up to MAX_BOOKS (10,000) even if there are only 2 books.
//    A failed search always checks all 10,000 slots.
for (auto& b : books)
    if (b.name == name) return b.id;

// ✅ Goes up to the number of real books
for (int i = 0; i < total_books; i++)
    if (books[i].name == name) return books[i].id;
```

- The early `return` only helps when a match **exists**. A miss (the most common case for "does this exist?" checks) always goes through the whole array.
- Bounding by the array size costs O(MAX). Bounding by the record count costs O(N).

> **Takeaway:** With fixed arrays, loop up to the **counter** (`total_books`, `borrowed_count`), never up to the capacity.

---

## 4. The "empty slot" trap

**My question:** *"I don't understand why looping only up to `borrowed_count` fixes `is_this_book_exists` (now `book_index`)."*

**What was wrong:** The loop checked all `MAX_BORROWED` slots of `borrowed_books_ids`. The unused slots don't hold real data, and the first book's ID is `0`, so an unused slot that happens to contain `0` looks like "this user borrowed book 0". That's a **false positive**.

```cpp
// ❌ Checks slots that were never written
for (int i = 0; i < MAX_BORROWED; i++)
    if (borrowed_books_ids[i] == book_id) return i;

// ✅ borrowed_count acts as a fence around the valid data
int book_index(int book_id) const {
    for (int i = 0; i < borrowed_count; i++)
        if (borrowed_books_ids[i] == book_id) return i;
    return -1;
}
```

> [!IMPORTANT]
> **Correction to my original note:** I first wrote down that "empty array slots default to `0`". In this code, that isn't guaranteed. `User` has a user-provided constructor (`User() {}`) that does **not** initialize `borrowed_books_ids`, so the unused slots hold **indeterminate (garbage) values**. They're often `0` in practice, which is how the bug showed up. Either way, the fix is the same: never read past `borrowed_count`. To be safe, also write `int borrowed_books_ids[MAX_BORROWED] = {};`.

> **Takeaway:** Only data inside `[0, count)` is real. Everything after that is undefined, whether it looks like zeros or garbage.

---

## 5. Titles vs. copies

**My question:** *"`amount` is the number of copies, so if `total_books + amount` is more than `MAX_BOOKS`, we can't run `add_book`. Right?"*

**What was wrong:** I mixed up **rows** with **inventory**.

| Concept | Where it lives | Limited by |
| :--- | :--- | :--- |
| A distinct title (`CppHowToProgram`) | One slot in `books[]` | `MAX_BOOKS` |
| Number of copies of that title (`7`) | An `int` field **inside** that slot | Nothing (it's just a number) |

```cpp
// ❌ if (total_books + amount > MAX_BOOKS) ...
// ✅ A new title always uses exactly one slot
if (total_books == MAX_BOOKS)
    throw invalid_argument("Library is full, no room for more books!");
```

> **Takeaway:** One title = one row. The number of copies is a field in that row, not more rows.

---

## 6. Entity ID vs. array index

**What I did:** When a user returned a book, I passed `book_id` straight into `left_shift`.

**What was wrong:** `left_shift(index)` expects a **position in the user's `borrowed_books_ids` array** (0–9). A book ID is a **name tag** (it could be `105`). Starting the shift at "position 105" reads and writes outside the array.

```cpp
// ❌ Mixes up an ID with a position
users[user_id].left_shift(book_id);

// ✅ Find the position first (reusing the helper, DRY), then shift
int index = users[user_id].book_index(book_id);
if (index == -1) { /* user didn't borrow it */ return; }
users[user_id].left_shift(index);
users[user_id].borrowed_count--;
```

> **Takeaway:** An **ID** says *which thing*. An **index** says *where it is in this particular array*. They're only the same by design (see #9). Inside the user's small list, they're unrelated.

---

## 7. `std::sort` comparators and prefix matching

**My question:** *"What's wrong, and why?"* (when `std::sort` rejected my comparators and the prefix search printed the wrong books)

### 7a. Comparators must not be regular member functions

A regular member function has a hidden `this` parameter, so its real signature is something like `bool (Library*, const Book&, const Book&)`. `std::sort` calls `cmp(a, b)` with **two** arguments, so it can't use it.

```cpp
// ❌ bool sort_by_id(const Book& a, const Book& b) { ... }   // regular member function

// ✅ static removes the hidden this, so it's a plain function
static bool sort_by_id(const Book& b1, const Book& b2) { return b1.id < b2.id; }
sort(temp, temp + total_books, sort_by_id);
```

A lambda also works: `sort(first, last, [](const Book& a, const Book& b){ return a.id < b.id; });`

### 7b. "Contains" is not "starts with"

```cpp
// ❌ Matches the prefix ANYWHERE: "Java" would match "CoreJava"
if (name.find(prefix) != string::npos)

// ⚠️ Correct, but find() keeps scanning the whole string when there's no match at position 0
if (name.find(prefix) == 0)

// ✅ Final version: only checks starting at position 0
if (books[i].name.rfind(prefix, 0) == 0)

// ✅ C++20, the clearest option
if (books[i].name.starts_with(prefix))
```

> **Takeaway:** Comparators passed to algorithms must be free functions, `static` members, or lambdas. For prefix checks, use `starts_with` (C++20) or `rfind(prefix, 0) == 0`.

---

## 8. Const correctness

**My question:** *"I made a `void print_user()` function inside `User`, but `for (const auto& u : users) { u.print_user(); }` gives an error about const. What does const actually mean here?"*

**What was wrong:** `const auto& u` promises the compiler that `u` won't be modified. A member function without `const` at the end **might** modify the object, so the compiler won't let you call it on a const object.

```cpp
// ❌ void print_user() { ... }

// ✅ const at the end promises this function doesn't modify the object
void print_user() const { ... }
int  book_index(int book_id) const { ... }
```

> **Takeaway:** Mark every member function that only reads data as `const`. Do it from the start. Adding `const` later spreads through the whole codebase.

---

## 9. Sorting the master array breaks foreign keys

**Final review:** sorting and printing.

**What was wrong:** The whole design relies on **`books[id]` being the book with that ID** (O(1) access), and users store book IDs as foreign keys. Calling `std::sort` on `books[]` moves records to new positions:

```text
Before sort (by name):  books[0]=Zoology(id 0)  books[1]=Algebra(id 1)
After sort:             books[0]=Algebra(id 1)  books[1]=Zoology(id 0)
A user holding id 0 → books[0] → "Algebra"  ❌ wrong book
```

**Fix:** Sort a **temporary copy**, print it, and free it.

```cpp
// ✅ Final version
void print_books_sorted(bool (*cmp)(const Book&, const Book&)) {
    Book* temp = get_books_copy();          // new Book[total_books], copy of the real books
    sort(temp, temp + total_books, cmp);
    for (int i = 0; i < total_books; i++) temp[i].print_book();
    delete[] temp;                          // every new[] needs a matching delete[]
}
```

> [!TIP]
> **Next step:** Manual `new[]`/`delete[]` leaks memory if an exception is thrown between them. `std::vector<Book> temp(books, books + total_books);` makes the same copy and frees itself automatically (RAII).

> **Takeaway:** If position *is* the key, never reorder the original. Reorder a copy, or an array of indexes/pointers that refer to it.

---

## 10. Linker error from a `static` array size

**What happened:** `MAX_BORROWED` was a `static const` member used as an array size and passed to `std::format`. The program compiled but **failed to link** with an "undefined reference" error.

**Why:** Before C++17, a `static const int` declared inside a class has no definition, only a declaration. Anything that takes its address or binds a reference to it (and `std::format` takes its arguments by reference) needs a real definition, which didn't exist.

```cpp
// ❌ static const int MAX_BORROWED = 10;   // declaration only, may fail to link

// ✅ inline (C++17) gives it exactly one definition, so no separate .cpp definition is needed
inline static constexpr int MAX_BORROWED = 10;
```

> **Takeaway:** For class constants, use `static constexpr`. It's implicitly `inline` from C++17 on, and writing `inline` explicitly makes the intent clear.

---

## 11. Stack overflow from a huge local object

**What happened:** `Library lib;` in `main` holds 10,000 `Book`s and 10,000 `User`s, about **1.4 MB**. The default stack on Windows is **1 MB**, so the program can crash at startup before printing anything.

```cpp
// ❌ Library lib;                           // ~1.4 MB on the stack

// ✅ Allocated on the heap, freed automatically when main returns
auto lib = make_unique<Library>();
lib->add_book();
```

> **Takeaway:** Large fixed-size objects belong on the heap (`make_unique`, or `std::vector` internally), not in a local variable.

---

## 12. Mixing `cin >>` and `getline`

**What happened:** After `cin >> choice`, the next `getline` read an **empty line**, because `>>` leaves the `\n` in the input buffer. Invalid input like `abc` also put `cin` into a fail state and caused an infinite menu loop.

```cpp
// ✅ Final version: all input is read with getline, then parsed
int read_int(const string& prompt) {
    while (true) {
        string s = read_line(prompt);
        try {
            size_t pos = 0;
            int v = stoi(s, &pos);
            if (pos == s.size()) return v;   // reject "12abc"
        } catch (...) {}
        error("Please enter a valid number.");
    }
}
```

`main` also stops the loop when stdin closes (`if (!cin) break;`), so piped input or Ctrl+Z doesn't cause an endless error loop.

> **Takeaway:** Choose one input style. Reading whole lines and parsing them is the most robust.

---

## Checklist for the Next Project

- [ ] Get the data model reviewed **before** building features (#2).
- [ ] Every loop over a fixed array is bounded by the record count, not the capacity (#3, #4).
- [ ] Arrays are initialized (`= {}`), and nothing reads past `count` (#4).
- [ ] IDs and indexes are kept separate, or the design guarantees `id == index` (#6, #9).
- [ ] All read-only member functions are marked `const` (#8).
- [ ] Comparators are `static` or lambdas (#7).
- [ ] Never sort data whose position is used as a key (#9).
- [ ] Class constants are `static constexpr` (#10).
- [ ] Large objects live on the heap, preferably through RAII (`vector`, `unique_ptr`) (#9, #11).
- [ ] All input goes through one validated, line-based reader (#12).
