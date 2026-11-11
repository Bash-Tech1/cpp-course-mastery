# Hospital System (Console-Based Queue Management)

A C++ console application that simulates a hospital management system. It handles patient registrations, priority queues based on medical urgency, and doctor consultations across multiple medical specializations.

---

## Features

* **20 Specializations**: Supports up to 20 different medical departments (e.g., Children, Surgery, etc.).
* **Capacity Limit**: Each specialization maintains a strict queue limit of a maximum of **5 available spots**.
* **Priority Queueing**: 
  * **Urgent patients (Status = 1)** are added to the **beginning** of the queue.
  * **Regular patients (Status = 0)** are added to the **end** of the queue.
* **Live Status Display**: Prints waiting patients categorized by their respective specializations.
* **Doctor Pickup**: Allows doctors to call the next patient in line for a specific specialization, automatically removing them from the queue.

---

## How It Works / Menu Options

When you run the program, you will be presented with a menu of choices:

1. **Add new patient**: 
   * Enter the specialization number (`1` to `20`).
   * Enter the patient's name and status (`0` for regular, `1` for urgent).
   * *Note:* If the department already has 5 patients, the system will apologize and reject the addition.
2. **Print all patients**: Displays all waiting patients across all active specializations.
3. **Get next patient (Doctor pickup)**: 
   * Enter the specialization number. 
   * If no patients are waiting, the system informs the doctor. Otherwise, it calls the patient forward and removes them from the queue.
4. **Exit**: Closes the application.

---

