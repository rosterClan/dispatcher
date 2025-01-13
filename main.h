#ifndef MAIN_H
#define MAIN_H
    typedef struct result {
        int t0;
        int t1; 
        int t2; 
        int w;
        float turnaround; 
        float responce; 
        float waiting; 
    } result;

    extern result * create_result(int, int, int, int, float, float, float);
#endif