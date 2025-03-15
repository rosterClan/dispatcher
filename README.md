<br />
<div align="center">
  <a href="">
    <img src=" " alt="Logo">
  </a>
  <h3 align="center">Multi-level Frequency Queue CPU Dispatcher</h3>
</div>

## About The Project
This project implements a **Multi-Level Queue (MLQ) Dispatcher** for a **uniprocessor system**, simulating job scheduling with priority-based queues. The dispatcher schedules randomly generated jobs based on their **arrival time, execution time, and priority (0, 1, or 2)**.  

## Features  

- **Three-Level Ready Queue**  
  - **Level-0:** First Come First Served (FCFS) with highest priority.  
  - **Level-1:** FCFS, pre-empted by Level-0 jobs, and demoted to Level-2 if not completed in time.  
  - **Level-2:** Round Robin (RR), pre-empted by higher-priority jobs, and recycled if unfinished.  

- **Starvation Prevention**  
  - Jobs waiting too long in lower levels are promoted back to Level-0.  

- **Performance Metrics**  
  - Calculates **average turnaround time, waiting time, and response time**.  


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

2: I wrote this assignment in a Windows development environment. To run the code, open your CMD and navigate to the current working directory (i.e., the directory in which this README file is stored). Then, you can run the following script to activate the Python virtual environment:
```sh
.venv\Scripts\activate
```

Once the virtual environment is activated, you should be able to open and run Assignment.py.

## Contact
William Walker - william.sinclair.walker@gmail.com

