# CPU Scheduling

A simulation of multiple CPU scheduling algorithms made in C++.

## How to Run

1. Clone/download whole repository, or only Scheduling.exe.
2. Double-click Scheduling.exe to run.
3. Enter number of processes to be performed (min 3, max 10).
4. Enter details of burst time, arrival time, and priority for each process.
5. Choose scheduling method to be ran.
6. Key in 0 as choice to close the application.

## Scheduling Algorithm Behaviours

### 1. First Come First Served-based (FCFS) pre-emptive Priority

- Scheduling is based on priority
- When two or more processes have the same priority, the process which arrived first is selected.
- If a new process arrives with a higher priority, it will pre-empt(stall) the current running process.
- Smaller number indicates higher priority.

### 2. Round Robin Scheduling with Priority

- Each process is ran for the specified time quantum.
- Another process with the highest priority will be chosen for the next run.
- If there are multiple processes with the same priority, the one that has been longest in the queue will be chosen.
- If there is no other process, the same one will be run again.

### 3. Three-level Queue Scheduling

- The scheduling is partitioned into three queues.
- Processes are assigned on respective queues based on their priority level.
- The queues are then implemented as fixed-priority pre-emptive scheduling, where processes in higher numbered queues are preempted if a new process enters a lower numbered queue, and only ran again if the lowered number queues are empty.

Queue Behaviours:

| Queue | Priority | Scheduling Algorithm   |
| ----- | -------- | ---------------------- |
| 1     | 1 & 2    | Round robin            |
| 2     | 3 & 4    | First come first serve |
| 3     | 5 & 6    | First come first serve |

### 4. Shortest Remaining Time Next (SRTN) Scheduling with Priority

- Pre-emptive version of Shortest Job First (SJF) algorithm.
- Processes with shortest CPU burst time are performed first.
- Shorted CPU burst time precedes priority level.
- If multiple shortest burst processes are having similar times, only then priority comparison takes places.
- Rescheduling is performed each time a new process enters the queue.
