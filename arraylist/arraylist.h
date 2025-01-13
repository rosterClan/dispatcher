
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

    typedef struct ArrayList {
        void ** data; 
        int size; 
    } ArrayList; 

    extern ArrayList * create_arraylist();
    extern void append_to_arraylist(void *, ArrayList *);
    extern void * get_item(int, ArrayList *);
    extern void remove_item_by_idx(int, ArrayList *);
    extern void remove_item(void *, ArrayList *);

#endif