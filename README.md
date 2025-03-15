<br />
<div align="center">
  <h3 align="center">Multi-level Frequency Queue CPU Dispatcher</h3>
</div>

## About The Project
This project implements a Multi-Level Queue (MLQ) Dispatcher for a uniprocessor system, simulating the behavior of a real-world job scheduler—a critical component of an operating system responsible for managing how processes are assigned CPU time. The dispatcher orchestrates job execution using priority-based queues, ensuring that high-priority tasks are executed first while maintaining mutual exclusion, meaning only one job runs on the CPU at any given time. This prevents conflicts, race conditions, and inefficient resource contention. The simulated jobs represent computational tasks with different arrival times, execution durations, and priority levels, demonstrating how modern operating systems handle multi-tasking and process scheduling.

## Features  

- **Mutual Exclusion & Concurrency Control**  
  - Ensures that only **one job executes at a time** to maintain **data integrity**.  
  - Proper synchronization prevents race conditions when moving jobs between queues.  

- **Three-Level Ready Queue**  
  - **Level-0 (Highest Priority):** First Come First Served (FCFS). Jobs run without interruption unless they exceed their time-quantum.  
  - **Level-1 (Medium Priority):** FCFS, pre-empted by Level-0 jobs. If not completed in time, jobs are demoted to Level-2.  
  - **Level-2 (Lowest Priority):** Round Robin (RR), pre-empted by higher-priority jobs, and recycled if unfinished.  

- **Starvation Prevention**  
  - Jobs waiting too long in lower levels are promoted back to Level-0, ensuring fairness.  

- **Performance Metrics**  
  - Computes **average turnaround time, waiting time, and response time**.  

## Additional Comments  

- Implemented in **C/C++** with a focus on **synchronization and mutual exclusion**.  
- Accepts user-defined **time-quantum values (t0, t1, t2) and starvation threshold (W)**.  
- Includes a **Makefile** for compilation on the university’s servers.  
- Well-commented and structured code for maintainability.  


### Built With
<a href="">
  <img src="https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white" alt="C">
</a>
<a href="">
  <img src="https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54" alt="python">
</a>
<a href="">
  <img src="https://img.shields.io/badge/PowerShell-%235391FE.svg?style=for-the-badge&logo=powershell&logoColor=white" alt="python">
</a>

## Getting Started
This is an example of how you may give instructions on setting this project locally. Clone this repo and then perform the following steps. 

### Prerequisites
1: Clone the repo

2: I wrote this assignment in a Windows development environment running WSL. However, you should be able to run the necessary binary in a normal windows context. Navigate to the working directory and run: 
```sh
./run_me test_1.txt
```
3: You'll then need to enter relevent time-quantum values alongside a starvation counter, for example: 
```sh
5 10 15 20
```

The system will then output metrics regarding average turnaround time, waiting time, and response time of simulated jobs. 

## Contact
William Walker - william.sinclair.walker@gmail.com

