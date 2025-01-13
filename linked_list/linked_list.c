#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

linked_list * create_linked_list() {
    linked_list * new_list = malloc(sizeof(linked_list));
    new_list->head = NULL; 
    new_list->tail = NULL; 
    new_list->size = 0; 
    return new_list; 
}

node * create_node(void * data) {
    node * n_node = malloc(sizeof(node));
    n_node->nxt = NULL;
    n_node->data = data;
    return n_node;
}

void destroy_linked_list(linked_list * d_list) {
    node * cur_node = d_list->head; 
    while (cur_node != NULL) {
        node * nxt = cur_node->nxt; 
        destroy_node(cur_node);
        cur_node = nxt;
    }

    d_list->head = NULL;
    d_list->tail = NULL; 
    free(d_list);
}

void destroy_node(node * d_node) {
    d_node->nxt = NULL; 
    free(d_node);
} 

node * get_node_by_idx(int idx, linked_list * new_list) {
    if (new_list->size <= 0 || idx >= new_list->size) {
        return NULL;
    }
    int counter = 0; 
    node * cur_node = new_list->head;
    while (cur_node != NULL && counter != idx) {
        cur_node = cur_node->nxt;
        counter++; 
    }
    return cur_node;
}

void append_node_infront(node * n_node, linked_list * new_list) {
    if (new_list->size == 0) {
        new_list->head = n_node;
        new_list->tail = n_node; 
    } else {
        n_node->nxt = new_list->head;
        new_list->head = n_node;
    }
    new_list->size++; 
}

void append_node_behind(node * n_node, linked_list * new_list) {
    if (new_list->size == 0) {
        new_list->head = n_node;
        new_list->tail = n_node; 
    } else {
        new_list->tail->nxt = n_node;
        new_list->tail = n_node;
        n_node->nxt = NULL; 
    }
    new_list->size++; 
}

node * pop_back(linked_list * new_list) {
    node * r_node = NULL;
    if (new_list->size == 0) {
        return r_node; 
    } 
    
    if (new_list->size == 1) {
        r_node = new_list->head;
        new_list->head = NULL; 
        new_list->tail = NULL; 
        new_list->size--; 
    } else {
        r_node = new_list->tail;
        node * cur_node = new_list->head; 
        while (cur_node->nxt != new_list->tail) {
            cur_node = cur_node->nxt;
        }
        cur_node->nxt = NULL; 
        new_list->tail = cur_node; 
        new_list->size--; 
    }

    r_node->nxt = NULL; 
    return r_node;
}


node * pop_front(linked_list * new_list) {
    node * r_node = NULL;
    if (new_list->size == 0) {
        return r_node; 
    } 
    
    if (new_list->size == 1) {
        r_node = new_list->head; 
        new_list->head = NULL;
        new_list->tail = NULL; 
    } else {
        r_node = new_list->head; 
        new_list->head = new_list->head->nxt;
    }

    new_list->size--;
    r_node->nxt = NULL; 
    return r_node;
}

