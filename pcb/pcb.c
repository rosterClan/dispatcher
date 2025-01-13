#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "pcb.h"

pcb * create_pcb(int arrival_time, int cpu_time, int priority, char label) {
    pcb * n_pcb = malloc(sizeof(pcb));

    n_pcb->arrival_time = arrival_time; 

    n_pcb->first_start = -1; 
    n_pcb->completion_time = -1; 

    n_pcb->cpu_time = cpu_time; 
    n_pcb->priority = priority;
    n_pcb->service_time = 0; 
    n_pcb->starvation_trigger = INT_MAX; 


    n_pcb->args[0] = "./process";
    n_pcb->args[1] = NULL;

    n_pcb->status = PCB_INITIALIZED; 
    n_pcb->label = label;

    return n_pcb; 
}

pcb * startPcb(pcb * p) {
    #ifndef DEBUG
        p->pid = fork();
        switch (p->pid) {
            case -1:
                fprintf(stderr, "FATAL: Could not fork process!\n");
                exit(EXIT_FAILURE);
            case 0:
                p->pid = getpid();
                p->status = PCB_RUNNING;
                fflush(stdout);
                execv("./process", p->args);
                fprintf(stderr, "ALERT: You should never see me!\n");
                exit(EXIT_FAILURE);
        }
    #endif

    p->status = PCB_RUNNING;
    return p;
}

pcb * interuptPcb(pcb * p) {
    int status;

    if (!p) {
        fprintf(stderr, "ERROR: Can not terminate a NULL process\n");
        return NULL;
    } else {
        #ifndef DEBUG
            kill(p->pid, SIGSTOP);
            waitpid(p->pid, &status, WUNTRACED);
        #endif
        p->status = PCB_INTERRUPTED;
        return p;
    }
}


pcb * suspendPcb(pcb * p) {
    int status;

    if (!p) {
        fprintf(stderr, "ERROR: Can not terminate a NULL process\n");
        return NULL;
    } else {
        #ifndef DEBUG
            kill(p->pid, SIGSTOP);
            waitpid(p->pid, &status, WUNTRACED);
        #endif
        p->status = PCB_SUSPENDED;
        return p;
    }
}

pcb * terminatePcb(pcb * p) {
    int status;
    if (!p) {
        fprintf(stderr, "ERROR: Can not terminate a NULL process\n");
        return NULL;
    }
    else {
        #ifndef DEBUG
            kill(p->pid, SIGINT);
            waitpid(p->pid, &status, WUNTRACED);
        #endif
        p->status = PCB_TERMINATED;
        return p;
    }
}

void destroy_pcb(pcb * d_pcb) {
    free(d_pcb);
}





