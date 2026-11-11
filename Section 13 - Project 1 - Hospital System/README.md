# Hospital System

## Project Overview
A console-based queue management system for a hospital. The system manages patient intakes and doctor pickups across 20 distinct medical specializations. It enforces strict queue limits and prioritizes urgent cases using foundational C++ array manipulation.

## Architecture and Design Decisions
To practice raw memory and array manipulation, this project strictly avoids structs, classes, and standard library containers (like `std::vector` or `std::queue`). 

State is maintained using **parallel arrays**:
* `string names[20][5];`: A 2D array storing patient names (20 specializations, up to 5 patients each).
* `int status[20][5];`: A 2D array storing patient urgency (0 = regular, 1 = urgent).
* `int queue_lengths[20];`: A 1D array tracking the current number of patients waiting in each specialization.

**Queue Mechanics (Manual Shifting):**
Because fixed arrays are used instead of dynamic queues, adding an urgent patient to the front (index 0) or removing a patient from the front (Doctor pickup) requires manually shifting all other elements right or left to prevent data overwriting or leaving empty gaps.

## Features Implemented
* **Add a Patient:** 
  * Accepts specialization [1-20], name, and urgency status.
  * Rejects addition if the specialization queue is full (5 patients).
  * Appends regular patients to the end of the queue.
  * Inserts urgent patients at the beginning of the queue by shifting existing patients right.
* **Print Patients:** Iterates through the 20 specializations and prints the waiting line. Skips specializations that have 0 patients.
* **Doctor Pickup:** Removes the first patient in the specified specialization's queue and shifts the remaining patients left to close the gap. Informs the doctor if the queue is already empty.

## Requirements
* C++11 or higher
* Core libraries: `<iostream>`, `<string>`

## Build and Run Instructions
```bash
# Compile the project
g++ -std=c++17 -Wall -Wextra main.cpp -o hospital_system

# Run the executable
./hospital_system