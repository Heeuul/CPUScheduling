# CPU Scheduling

A simulation of multiple CPU scheduling algorithms made in C++.

## How to Run

## Scheduling Algorithm Behaviours

### First Come First Served-based (FCFS) pre-emptive Priority

- Scheduling is based on priority
- When two or more processes have the same priority, the process which arrived first is selected.
- If a new process arrives with a higher priority, it will pre-empt(stall) the current running process.
- Smaller number indicates higher priority.

### Round Robin Scheduling with Priority

- Each process is ran for the specified time quantum
- Another process with the highest priority will be chosen for the next run
- If there are multiple processes with the same priority, the one that has been longest in the queue will be chosen
- If there is no other process, the same one will be run again

### Three-level Queue Scheduling

### Shortest Remaining Time Next (SRTN) Scheduling with Priority
