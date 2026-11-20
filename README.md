# CPU Process Scheduler

A console-based CPU Process Scheduler developed using **C++ and Data Structures & Algorithms (DSA)**. This project demonstrates how different CPU scheduling algorithms manage and execute processes.

## Features

- **FCFS Scheduling:** Executes processes in their arrival order using a Queue.
- **SJF Scheduling:** Executes processes with the shortest burst time first.
- **Priority Scheduling:** Schedules processes according to priority using a Priority Queue (Heap).
- **Process Management:** Add, display, search, update and delete processes.
- **Sorting & Filtering:** Organize processes based on burst time and priority.
- **Heap Visualization:** Demonstrates heap insertion and deletion operations.
- **Time Calculation:** Calculates completion time, waiting time and turnaround time.
- **Prefix & Suffix Sum:** Uses cumulative calculations for scheduling.
- **Operation History:** Keeps track of performed operations.
- **Sample Data:** Includes 15 sample processes and an option to reload them.

## Technologies Used

- C++
- Standard Template Library (STL)
- Data Structures and Algorithms

## Data Structures Used

| Data Structure | Application |
|---|---|
| Queue | FCFS Scheduling |
| Priority Queue (Heap) | Priority Scheduling |
| Vector | Process storage and sorting |

## How to Run

**1. Clone the repository**

```bash
git clone YOUR_REPOSITORY_URL
```

**2. Open the project folder**

**3. Compile the program**

```bash
g++ main.cpp -o scheduler
```

**4. Run the program**

```bash
./scheduler
```

On Windows, use:

```bash
scheduler.exe
```

## Scheduling Assumptions

- All processes are assumed to arrive at time zero.
- Scheduling algorithms are non-preemptive.
- A smaller priority number represents a higher priority.

## Project Objective

The main objective is to understand the practical implementation of CPU scheduling algorithms and learn how different data structures help manage processes efficiently.

---

**Project:** CPU Process Scheduler  
**Language:** C++  
**Category:** Data Structures and Algorithms
