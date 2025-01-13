#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "main.h"
#include "pcb.h"
#include "dispatcher.h"

void destroy_multilevel_queue(linked_list * multilevel_queue) {
    node * cur_node = multilevel_queue->head; 
    while (cur_node != NULL) {
        linked_list * queue = (linked_list *)cur_node->data;
        destroy_linked_list(queue);
        queue = NULL; 
        cur_node = cur_node->nxt;
    }
    destroy_linked_list(multilevel_queue);
}

void print_state(linked_list * multilevel_queue, int ticker) {
    node * cur_queue = multilevel_queue->head;
    int curQueue = 0; 
    while (cur_queue != NULL) {
        node * cur_node = ((linked_list *)(cur_queue->data))->head; 
        while (cur_node != NULL) {
            pcb * job = (pcb *)(cur_node->data);
            printf("Job: %c Level: %i priority: %i remaining: %i ticker: %i starvation_tick: %i\n",job->label, curQueue, job->priority, job->cpu_time, ticker, job->starvation_trigger);
            cur_node = cur_node->nxt;
        }
        cur_queue = cur_queue->nxt; 
        curQueue++; 
    }
}

pcb * run_job(linked_list * multilevel_queue, pcb * job, int remaining_quantum_time, int * reset_time, int * ticker, int nxtArrivalTime) {
    if (job->status == PCB_INITIALIZED) {
        job->first_start = *(ticker);
    }
    startPcb(job);
    while (1==1) {

        if (job->cpu_time <= 0) {
            job->completion_time = *(ticker);
            terminatePcb(job);
            break; 
        } else if (remaining_quantum_time == 0) {   
            suspendPcb(job);
            break;
        } else if (*(ticker) >= nxtArrivalTime) {
            interuptPcb(job);
            break;
        }
        
        #ifndef DEBUG
            sleep(1);
        #endif
       
        job->service_time++; 
        job->cpu_time--;
        remaining_quantum_time--;

        //#ifdef CUSTOM_DEBUG
        //    printf("%c\n", job->label);
        //    printf("--------\n");
        //    printf("RUNNING Job: %c level: %i remaining: %i ticker: %i starvation_tick: %i\n",job->label, job->priority, job->cpu_time, *(ticker), job->starvation_trigger);
        //    print_state(multilevel_queue, *(ticker));
        //#endif

        *(ticker) = *(ticker)+1;
    }
    job->starvation_trigger = *(reset_time);
}

void priority_manager(node * job_node, linked_list * multilevel_queue) {
    pcb * job = (pcb *)job_node->data;
    switch (job->status) {
        case PCB_SUSPENDED:
            if (job->priority < multilevel_queue->size-1) {
                job->priority++; 
            }
            break;
        case PCB_INTERRUPTED:
            break;
        case PCB_TERMINATED:
            destroy_pcb(job); 
            destroy_node(job_node);
            return;
    }

    node * node_wpr = get_node_by_idx(job->priority, multilevel_queue);
    linked_list * specific_queue = (linked_list *)node_wpr->data;
    append_node_behind(job_node, specific_queue);
}

void starvation_prevention(linked_list * multilevel_queue, int counter, int reset_time, int * setPriority) {
    int elevate = 0; 
    linked_list * base_queue = (linked_list *)((get_node_by_idx(0, multilevel_queue))->data);

    node * queue_node_wpr = get_node_by_idx(1, multilevel_queue);
    while (queue_node_wpr != NULL) {
        linked_list * specific_queue = (linked_list *)(queue_node_wpr->data);
        pcb * head = NULL;
        
        while (specific_queue->size > 0) { 
            if (head == NULL) {
                head = (pcb *)((specific_queue->head)->data);
            }
            
            if (head->starvation_trigger <= 0 || elevate == 1) {
                node * cur_node = pop_front(specific_queue);
                pcb * cur_job = (pcb *)(cur_node->data);
                cur_job->priority = 0; 
                append_node_behind(cur_node, base_queue);
                elevate = 1; 
                continue;
            }
            head->starvation_trigger--;
            break; 
        }

        queue_node_wpr = queue_node_wpr->nxt;
    }
    
}

int min(int a, int b) {
    if (a > b) {
        return b; 
    }
    return a; 
}

int max(int a, int b) {
    if (a > b) {
        return a; 
    }
    return b; 
}

int simulate_arrival_jobs(linked_list * multilevel_queue, linked_list * arrival_jobs, int * reset_time, int * ticker, int * curPriority) {
    int nxtArrival = INT_MAX;
    if (arrival_jobs->size > 0) {
        node * arrival_job_node = arrival_jobs->head; 
        pcb * arrival_job = (pcb *)arrival_job_node->data; 
        
        while (arrival_job->arrival_time <= *(ticker)) {
            pop_front(arrival_jobs);
            *(curPriority) = min(arrival_job->priority, *(curPriority));

            node * node_wpr = get_node_by_idx(arrival_job->priority, multilevel_queue);
            linked_list * local_queue = (linked_list *)node_wpr->data; 

            arrival_job->starvation_trigger = *(reset_time);
            append_node_behind(arrival_job_node, local_queue);
            
            if (arrival_jobs->size > 0) {
                arrival_job_node = arrival_jobs->head;
                arrival_job = (pcb *)arrival_job_node->data;
                continue;
            } 
            break;
        }

        if (arrival_job->priority < *(curPriority)) {
            nxtArrival = arrival_job->arrival_time;
        }

    }
    return nxtArrival;
}

void job_metrics(pcb *job, int *num_completed_tasks, int *sum_waiting, int *sum_turnaround, int *sum_response) {
    if (job->status == PCB_TERMINATED) {
        int turnaround_time = job->completion_time - job->arrival_time; 
        int waiting_time = turnaround_time - job->service_time; 
        int response_time = job->first_start - job->arrival_time;

        *sum_waiting += waiting_time; 
        *sum_turnaround += turnaround_time; 
        *sum_response += response_time; 
        (*num_completed_tasks)++; 

    }
}

void main_loop(int ** time_levels, int array_size, int * reset_time_counter, linked_list * arrival_jobs) {
    if (array_size <= 1) {
        exit(EXIT_FAILURE);
    }

    int reset_time = *(reset_time_counter);
    int ticker = 0; 

    int sum_waiting = 0;
    int sum_turnaround = 0; 
    int sum_response = 0;
    int num_completed_tasks = 0; 

    int nxtArrivalTime = 0;

    linked_list * multilevel_queue = create_linked_list();

    for (int idx = 0; idx < array_size; idx++) {
        linked_list * queue_level = create_linked_list();
        node * n_node = create_node((void *)queue_level);
        append_node_behind(n_node, multilevel_queue);
    }

    int queueIdx = 0; 
    node * job_node = NULL; 
    while (arrival_jobs->size > 0 || queueIdx < multilevel_queue->size) {
        queueIdx = min(multilevel_queue->size-1, queueIdx);

        nxtArrivalTime = simulate_arrival_jobs(multilevel_queue, arrival_jobs, &reset_time, &ticker, &queueIdx);
        node * wpr_node = get_node_by_idx(queueIdx, multilevel_queue);
        linked_list * local_queue = (linked_list *)wpr_node->data;
    
        job_node = pop_front(local_queue);

        if (job_node != NULL) {
            run_job(multilevel_queue,(pcb *)job_node->data, *(time_levels[queueIdx]), &reset_time, &ticker, nxtArrivalTime);
            job_metrics((pcb *)job_node->data, &num_completed_tasks, &sum_waiting, &sum_turnaround, &sum_response);
            priority_manager(job_node, multilevel_queue);
            starvation_prevention(multilevel_queue, ticker, reset_time, &queueIdx);
        } else {
            ticker++; 
            queueIdx++; 
        }

    }
    
    destroy_multilevel_queue(multilevel_queue);

    float average_waiting = (float)(sum_waiting) / num_completed_tasks;
    float average_turnaround = (float)(sum_turnaround) / num_completed_tasks;
    float average_response = (float)(sum_response) / num_completed_tasks;
    printf("%.2f,%.2f,%.2f\n", average_turnaround, average_response, average_waiting);
}






