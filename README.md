#CPU Scheduling Simulator (C++)

# Overview
This project is a **CPU Scheduling Simulator** implemented in **C++**.  
It reads process information from an input file and calculates **waiting times** using three CPU scheduling algorithms:

- **First Come First Serve (FCFS)**
- **Shortest Job First (SJF)**
- **Priority Scheduling**

The results are displayed in the **terminal** and written to an **output file**.

---

# Features
- Reads process data from `input.txt`
- Supports multiple queues (Queue 0 and Queue 1)
- Implements three scheduling algorithms:
  - FCFS
  - SJF (non-preemptive)
  - Priority (non-preemptive)
- Outputs results to:
  - Terminal
  - Output file (`output.txt`)
- Uses linked lists to manage processes

---

## Input Format
Each line in the input file represents one process in the format:
5:2:0:0
3:1:1:0
8:3:2:1
6:2:3:1



# Field Description
| Field        | Description |
|--------------|-------------|
| burst_time   | CPU burst time |
| priority     | Process priority (lower value = higher priority) |
| arrival_time | Process arrival time |
| queue_id     | Queue number (0 or 1) |


---


# Output
The program calculates and prints **waiting times** for each process under each scheduling algorithm.


# Output Includes
- **Queue 0**:
  - FCFS
  - SJF
  - Priority
- **Queue 1**:
  - FCFS
  - SJF
  - Priority


The output is displayed in the terminal and saved in the output file.


### Example Output

Queue 0 FCFS:
0 5 8

Queue 0 SJF:
0 3 7

Queue 0 Priority:
0 2 6



---


# Scheduling Algorithms


# First Come First Serve (FCFS)
- Processes are executed in order of **arrival time**
- Simple implementation
- Can cause long waiting times


# Shortest Job First (SJF)
- Selects the process with the **smallest burst time**
- Non-preemptive
- Minimizes average waiting time


# Priority Scheduling
- Selects the process with the **highest priority**
- Lower priority number = higher priority
- Non-preemptive


---


## Compilation
Compile the program using `g++`:


(Replace main.cpp with your actual source file name if different.)

Execution

Run the program with input and output file names:

./cpu_scheduler input.txt output.txt
Files

main.cpp – Source code

input.txt – Input file containing process data

output.txt – Output file containing waiting times

cmpe351.h – Header file (provided by course)

Notes

Waiting times are reset between algorithms

Input file must be correctly formatted

Linked lists are used for process management

Author
Farzad Rahmani