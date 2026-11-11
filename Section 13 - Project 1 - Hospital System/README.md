
# Hospital System

A console-based queue management system for a hospital, written in C++. It manages patient intake and doctor pickups across 20 medical specializations, enforces a strict queue limit, and gives urgent patients priority.

## Problem Statement

- The hospital has **20 specializations** (e.g., Children, Surgery).
- Each specialization has only **5 waiting spots** (a queue).
- **Adding a patient:**
  - Read the specialization `[1-20]`, the patient's name, and status (`0` = regular, `1` = urgent).
  - If the queue already holds 5 patients, apologize and reject the patient.
  - Regular patients join the **end** of the queue; urgent patients join the **front**.
- **Printing:** Lists only the specializations that have waiting patients.
- **Doctor pickup:**
  - Read the specialization. If nobody is waiting, inform the doctor.
  - Otherwise, ask the first patient to go with the doctor and remove them from the queue.

## Design Decisions

This project deliberately avoids structs, classes, and standard containers (`std::vector`, `std::queue`). The goal is to practice fixed-size array manipulation and index management.

State is stored in two parallel 2D arrays plus a length counter per specialization:

| Variable | Type | Purpose |
|---|---|---|
| `names[20][5]` | `string` | Patient names, one row per specialization. |
| `status[20][5]` | `int` | Patient urgency (`0` = regular, `1` = urgent), using the same indices as `names`. |
| `queue_lengths[20]` | `int` | Number of patients currently waiting in each specialization. |

> Users enter specializations as `1-20`; internally, they map to array indices `0-19`.

### Queue Mechanics (Manual Shifting)

Fixed arrays do not provide queue operations automatically, so insertion and removal at the front must be implemented manually using element shifting.

- **Urgent patient:** Shift every existing element one position to the right, iterating backward to prevent overwriting existing data, then insert the new patient at index `0`.
- **Doctor pickup:** Remove the element at index `0`, then shift every remaining element one position to the left to close the gap.
- **Regular patient:** Write directly at index `queue_lengths[spec]`.

Both `names` and `status` must be shifted together to keep patient information synchronized.

### Time Complexity

Let `n` represent the number of patients waiting in the selected specialization.

| Operation | Time Complexity |
|---|---|
| Add regular patient | O(1) |
| Add urgent patient | O(n) |
| Doctor pickup | O(n) |
| Print all patients | O(20 + P) |

Where `P` represents the total number of waiting patients across all specializations.

Since each specialization has a maximum capacity of 5 patients, the actual number of shifting operations is very small.

## Features

### 1. Add a Patient
- Accepts a specialization number, patient name, and urgency status.
- Rejects the patient when the selected queue is full (5 patients).
- Appends regular patients to the end of the queue.
- Inserts urgent patients at the front by shifting existing entries to the right.

### 2. Print Patients
- Iterates over all 20 specializations and prints their waiting lists.
- Skips specializations with no waiting patients.
- Displays patients in their current queue order.

### 3. Doctor Pickup
- Accepts a specialization number.
- Informs the doctor if the selected queue is empty.
- Otherwise, identifies the first patient and removes them from the queue.
- Shifts remaining entries to maintain the correct queue order.

## Example Session

The following session illustrates the expected program behavior. Menu wording may vary depending on the implementation.

```text
Enter your choice:
1) Add new patient
2) Print all patients
3) Get next patient
4) Exit

> 1
Enter specialization (1-20): 3
Enter name: Ahmed
Enter status (0 = regular, 1 = urgent): 0

> 1
Enter specialization (1-20): 3
Enter name: Sara
Enter status (0 = regular, 1 = urgent): 1

> 2
Specialization 3: 2 patients
Sara (urgent)
Ahmed (regular)

> 3
Enter specialization (1-20): 3
Sara, please go with the doctor.
```

## Assumptions and Limitations

- Patient information is stored in memory only; data is lost when the program exits.
- The system supports exactly 20 specializations, each with a maximum capacity of 5 patients.
- Urgent patients are inserted at the very front, so a newer urgent patient is served before an earlier urgent patient.
- Input validation for out-of-range specialization numbers and non-numeric input is not implemented.

## Requirements

- A C++11-compatible compiler (e.g., GCC or Clang).
- Standard libraries only: `<iostream>`, `<string>`.

## Build and Run

Compile:

```bash
g++ -std=c++11 -Wall -Wextra main.cpp -o hospital_system
```

Run:

```bash
./hospital_system
```

## Possible Improvements

- Refactor patient data into a `struct Patient` and implement the queue using a class.
- Replace manual shifting with a circular buffer or `std::deque`.
- Add input validation and recover gracefully from invalid input.
- Preserve FIFO order among urgent patients instead of inserting every urgent patient at the front.
- Persist patient queues to a file so data survives between program executions.
