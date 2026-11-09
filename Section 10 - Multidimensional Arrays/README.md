Search how exactly the 2d array is represented in memory 
Understanding why raw arrays fail and how `std::vector` fixes them is one of the most important milestones in learning C++.

Let’s break this down into three parts: **the problems with raw arrays**, **why `std::vector` exists**, and **how `std::vector` solves those problems under the hood**.

---

### **Part 1: The Deep Problems with Raw Arrays**

When you write something like `int ar[1000][1000];` inside a class or function, you run into three massive architectural walls:

#### **1. The Stack Overflow Trap (Memory Location)**

* **The Problem:** Local variables, function parameters, and fixed-size arrays declared inside classes/functions are stored on the **Stack**.
* **What is the Stack?** The stack is a tiny, high-speed region of memory set aside for your program by the operating system—usually limited to **1 MB to 8 MB total**.
* **The Math:** An `int` takes 4 bytes. A $1000 \times 1000$ grid requires:

$$\text{1,000} \times \text{1,000} \times \text{4 bytes} = \mathbf{4,000,000 \text{ bytes}} = \mathbf{4 \text{ MB}}$$



If you add your `bool` flags, it climbs even higher. This comes dangerously close to or completely exceeds the total stack limit. The moment you instantiate your `Robot` class, the program crashes instantly with a **Segmentation Fault** or **Stack Overflow** before `main()` even gets going.

#### **2. Compile-Time Rigidity (Inflexibility)**

* **The Problem:** Raw arrays require their size to be known **at compile-time** (hardcoded numbers like `1000`).
* **Why it hurts:** If a user inputs $N = 5$ and $M = 5$, your raw array still forces the computer to reserve space for 1,000,000 cells. You are wasting 99.99% of your memory just in case the user wants a large grid. Worse, if the user inputs $N = 2000$, your fixed array of size 1000 is too small, and your program will crash or write over memory it shouldn't.

#### **3. Pointer Decay and Safety Blindness**

* **The Problem:** Raw arrays don't actually know their own size. When you pass a raw array to a function, it "decays" into a raw pointer (`int*`). The function completely forgets how many rows or columns it has. You have to manually pass `n` and `m` everywhere, and if you accidentally access `ar[50][50]` when the grid is only $5 \times 5$, C++ won't stop you—it will just read random memory, leading to unpredictable bugs or security vulnerabilities.

---

### **Part 2: Why You Should Use `std::vector**`

`std::vector` is part of the C++ Standard Template Library (STL). It is a wrapper around a dynamically allocated array designed to handle all the dangerous memory management for you while performing just as fast as a raw array.

---

### **Part 3: Exactly How `std::vector` Solves the Problems**

#### **1. It Uses the Heap (Solving Stack Overflow)**

Instead of storing its data on the tiny Stack, a `std::vector` stores its elements on the **Heap** (also known as free store).

* **What is the Heap?** The heap is a massive pool of system memory (equal to your computer's RAM, e.g., 8 GB, 16 GB, or more).
* **How it solves the problem:** Even if you make a vector of size $10,000 \times 10,000$, it lives safely on the heap where there is plenty of room, completely eliminating Stack Overflow crashes.

#### **2. Dynamic Allocation at Runtime (Solving Inflexibility)**

A vector's size does not need to be known at compile time.

* When your program runs and gets `cin >> n >> m;`, you can initialize your vector right then and there:
```cpp
vector<vector<Cell>> ar(n, vector<Cell>(m));

```


* If the user enters $3 \times 3$, it allocates precisely 9 cells. If they enter $500 \times 500$, it allocates 250,000 cells. **Zero memory is wasted.**

#### **3. RAII and Automatic Cleanup (Solving Memory Leaks)**

If you try to avoid vectors by manually allocating memory on the heap using pointers and `new` (e.g., `new int*[rows]`), you become responsible for manually writing `delete[]` statements later. If you forget, your program suffers from a **memory leak**.

* **How `vector` solves this:** `vector` follows a principle called **RAII** (*Resource Acquisition Is Initialization*).
* When the vector is created, it grabs memory from the heap. When the vector goes out of scope (e.g., your function ends or the object is destroyed), **its destructor automatically frees the heap memory for you**. You never have to worry about memory leaks.

#### **4. It Keeps Metadata (Safety and Convenience)**

A vector knows its own size. You can ask `ar.size()` or `ar[0].size()` at any time. It also prevents you from losing track of dimensions, and it can be safely passed into functions by reference (`vector<vector<Cell>>& ar`) without decaying into a blind pointer.
