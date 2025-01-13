#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef PCB_H
#define PCB_H

    #define PCB_UNINITIALIZED 0
    #define PCB_INITIALIZED 1
    #define PCB_READY 2
    #define PCB_RUNNING 3
    #define PCB_SUSPENDED 4
    #define PCB_TERMINATED 5
    #define PCB_INTERRUPTED 6

    typedef struct pcb {
        pid_t pid;
        char *args[3];

        int arrival_time;

        int first_start;
        int completion_time;

        int cpu_time;
        int priority;
        int service_time; 

        int starvation_trigger;

        int status;
        char label; 
    } pcb;

    extern pcb * create_pcb(int, int, int, char);
    extern void destroy_pcb(pcb *);
    extern pcb * terminatePcb(pcb *);
    extern pcb * suspendPcb(pcb *);
    extern pcb * startPcb(pcb *);
    extern pcb * interuptPcb(pcb * p);
#endif