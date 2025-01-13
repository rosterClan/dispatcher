#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "pcb.h"
#include "dispatcher.h"

result * create_result(int t0, int t1, int t2, int w, float turnaround, float responce, float waiting) {
    result * n_result = malloc(sizeof(result));
    n_result->t0 = t0;
    n_result->t1 = t1; 
    n_result->t2 = t2; 
    n_result->w = w; 

    n_result->turnaround = turnaround; 
    n_result->responce = responce; 
    n_result->waiting = waiting;

    return n_result;
}

void create_arrival(linked_list * arrival_queue, FILE * input_list_stream) {
    rewind(input_list_stream);
    char alphabet_test[1024] = "ABCDEFGHIJKLMNOPQRSTUZWZYX";
    int alphabetIdx = 0;
    int arrival_time, cpu_time, priority; 
    while (!feof(input_list_stream)) {
        if (fscanf(input_list_stream,"%d,%d,%d", &arrival_time, &cpu_time, &priority) != 2) {
            pcb * n_pcb = create_pcb(arrival_time, cpu_time, priority, alphabet_test[alphabetIdx]);
            node * n_node = create_node((void *)n_pcb);
            append_node_behind(n_node, arrival_queue);
            alphabetIdx++;
            if (alphabetIdx > 26) {
                alphabetIdx = 0; 
            }
        }
    }
}

int main (int argc, char *argv[])
{
    FILE * input_list_stream = NULL;
    if (argc <= 0)
    {
        fprintf(stderr, "FATAL: Bad arguments array\n");
        exit(EXIT_FAILURE);
    }
    else if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <TESTFILE>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char * test = argv[1];
    if (!(input_list_stream = fopen(argv[1], "r")))
    {
        fprintf(stderr, "ERROR: Could not open \"%s\"\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    printf("Provide t0, t1, t2 and starvation counter: \n");
    int time_1, time_2, time_3, w; 
    char line[256];
    if (fgets(line, sizeof(line), stdin) != NULL) {
        sscanf(line, "%i %i %i %i", &time_1, &time_2, &time_3, &w);
    }

    int * times[3];
    times[0] = &time_1;
    times[1] = &time_2;
    times[2] = &time_3;
    
    linked_list * arrival_queue = create_linked_list();
    create_arrival(arrival_queue, input_list_stream);
    
    main_loop(times, 3, &w, arrival_queue);
    destroy_linked_list(arrival_queue);

    
    return 0;
}