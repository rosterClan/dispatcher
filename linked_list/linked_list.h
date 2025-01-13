
#ifndef LINKED_H
#define LINKED_H
    typedef struct node {
        void * data; 
        struct node * nxt; 
    } node;

    typedef struct linked_list {
        node * head; 
        node * tail; 
        int size;
    } linked_list;

    extern linked_list * create_linked_list();
    extern node * create_node(void *);
    extern void destroy_linked_list(linked_list *);
    extern void destroy_node(node *);
    extern void append_node_infront(node *, linked_list *);
    extern node * pop_back(linked_list *);
    extern node * pop_front(linked_list *);
    extern node * get_node_by_idx(int, linked_list *);
    extern void append_node_behind(node *, linked_list *);

#endif