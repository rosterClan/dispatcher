#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>

ArrayList * create_arraylist() {
    ArrayList * list = malloc(sizeof(ArrayList));
    list->data = NULL;
    list->size = 0; 
    return list; 
}

void append_to_arraylist(void * item, ArrayList * list) {
    if (list->size == 0) {
        list->data = malloc(sizeof(void **));
        list->data[0] = item;
    } else {
        list->data = realloc(sizeof(void **) * (list->size+1));
        list->data[list->size] = item; 
    }
    list->size++;
}

void * get_item(int idx, ArrayList * list) {
    if (idx >= list->size) {
        return NULL; 
    }
    return list->data[idx];
}

void remove_item_by_idx(int idx, ArrayList * list) {
    void * item = get_item(idx, list);
    if (item != NULL) {
        remove_item(item, list);
    }
}

void remove_item(void * rem_item, ArrayList * list) {
    void ** new_list = malloc(sizeof(list->size));
    int new_idx = 0;
    int cur_idx = 0;
    
    void * item = get_item(cur_idx, list);
    while (item != NULL) {
        cur_idx++;
        if (rem_item == item) {
            continue;
        }
        new_list[new_idx] = item;
        new_idx++;

        item = get_item(cur_idx, list);
    }

    free(new_list->data);
    new_list->data = new_list;
}


