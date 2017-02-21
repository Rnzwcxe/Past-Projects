#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

//You are responsable for defining the dll
//  and dll_node structures.
//did it
struct dll{
    int size;
    node head;
    node tail;
            };
struct dll_node{
    void *data;
    node next;
    node previous;
            };

/**
 * Returns a new (empty) list.
 * You can define what an empty list is.
 * Precondition: There exists system memory to allocate
 *   a new empty dll structure.
 * Postcondition: A pointer to an empty list is returned.
 *   The returned list is a valid list.*/
list create_list(){
    list temp = malloc(sizeof(struct dll));
    temp->size = 0;
    temp->head = NULL;
    temp->tail = NULL;
    return temp;
}

/**
 * Frees all memory associated with the given list.
 * Precondition: l is a (possibly empty) list, that was
 *   originally produced with a call to the create_list
 *   function, and l has not already been freed.
 * Postcondition: l and all nodes contained within l are
 *   freed. Data contained within l is not freed.
 *   l is no longer a valid list.*/
 
//Could not figure out a proper way to test this one since it just messages the malloc thing
void destroy_list(list l){
    node to_del = l->head;
    while(to_del!=NULL){
        node temp = to_del->next;
        free(to_del);
        to_del = temp;
    }
    free(l);
    return;
}

/**
 * Returns the number of elements in the current list
 * Precondition: l is a valid list.
 * Postcondition: the number of elements in l is returned*/
int size(list l){
    return l->size;
}

/**
 * Returns whether or not the list is empty.
 * Precondition: l is a valid list.
 * Postcondition: Returns 0 iff l is empty.*/
int is_empty(list l){
    return (l->size) == 0;//just l->size should also work, but that seems like bad practice  unless one really wants efficency
}

/*
 * Appends data to l.
 * Precondition: l is a valid list.
 * Postcondition: l now contains a node that stores data.
 *   The size of l is now one larger.
 *   The new node is stored at the end of the list. */
void append(list l, void *data){
    node temp = malloc(sizeof(struct dll_node));
    temp->data = data;
    temp->next = NULL;
    temp->previous = l->tail;
    
    if (l->tail != NULL) l->tail->next = temp;
    if (l->size == 0) l->head = temp;
    if (l->size == 1) l->head->next = temp;
    l->tail = temp;
    l->size = (l->size)+1;
    return;
}

/*
 * Prepends data to l.
 * Precondition: l is a valid list.
 * Postcondition: l now contains a node that stores data.
 *   The size of l is now one larger.
 *   The new node is stored at the start of the list. */
void prepend(list l, void *data){
    node temp = malloc(sizeof(struct dll_node));
    temp->data = data;
    temp->previous = NULL;
    temp->next = l->head;
    
    if (l->head != NULL) l->head->previous = temp;
    if (l->size == 0) l->tail = temp;
    if (l->size == 1) l->tail->previous = temp;
    l->head = temp;
    l->size = (l->size)+1;
    return;
}

/*
 * Removes the first node from l.
 * Precondition: l is a valid list, and size(l) >= 1.
 * Postcondition: l now contains one less node.
 *   The node at the start of the list was removed.
 *   If size(l) was 1, the list is now empty.*/
void* remove_front(list l){
    node temp = l->head;
    
    if (l->size!=1) temp->next->previous = NULL;
    else l->tail = NULL;
    
    l->head = temp->next;
    free(temp);
    l->size = (l->size)-1;
}

/*
 * Removes the first node from l.
 * Precondition: l is a valid list, and size(l) >= 1.
 * Postcondition: l now contains one less node.
 *   The node at the end of the list was removed.
 *   If size(l) was 1, the list is now empty.*/
void* remove_back(list l){
    node temp = l->tail;
    
    if (l->size!=1) temp->previous->next = NULL;
    else l->head = NULL;
    
    l->tail = temp->previous;
    free(temp);
    l->size = (l->size)-1;
}

/*
 * Removes the first node from l containing data.
 * Precondition: l is a valid list, maybe empty.
 * Postcondition:  If data is in l, the node containing
 *   data that is nearest to the front of the list is 
 *   removed, and a non-zero value is returned. Otherwise,
 *   l is unchanged and 0 is returned.
 *   l is now one element smaller iff data was removed.
 *   If size(l) was 1, and data was removed, l is empty.*/
int remove_data(list l, void *data){
    node next_node = l->head;
    while(next_node!= NULL && next_node->data!=data){
        next_node = next_node->next;
    }
    if (next_node == NULL)
        return 0;
    else
        if (next_node != l->head) next_node->previous->next = next_node->next;
        if (next_node != l->tail) next_node->next->previous = next_node->previous;
        
        if (next_node == l->head)
            l->head = l->head->next;
        if (next_node == l->tail)
            l->tail = l->tail->previous;
        
        free(next_node);
        l->size = (l->size)-1;
        return 1;
}

/*
 * Removes n from l.
 * Precondition: l is a valid list, and n was returned by
 *   one of the other functions in this module when l was
 *   the input list to that function, and no remove
 *   functions have been called since n was returned.
 * Postcondition: n is removed from l.
 *   l is now one element smaller.
 *   If size(l) was 1, l is now empty.*/
void remove_dll(list l, node n){
    if (n != l->head) n->previous->next = n->next;
    if (n != l->tail) n->next->previous = n->previous;
    
    if (n == l->head)
        l->head = l->head->next;
    if (n == l->tail)
        l->tail = l->tail->previous;
    
    free(n);
    l->size = (l->size)-1;
}

/**
 * Returns the data from the node at the front of l.
 * Precondition: l is not empty.
 * Postcondition: Returns the data stored in the node
 *  at the front of l, l is unchanged.*/
void* peek_front(list l){
    return l->head->data;
}

/**
 * Returns the data from the node at the back of l.
 * Precondition: l is not empty.
 * Postcondition: Returns the data stored in the node
 *  at the back of l, l is unchanged.*/
void* peek_back(list l){
    return l->tail->data;
}

/**
 * Returns the data from n.
 * Precondition: l is not empty. n was returned by a call
 *   to one of the functions in this module, with l as the
 *   list argument. No calls to remove functions have been
 *   made since n was returned.
 * Postcondition: Returns the data stored in n.
 *  l is unchanged.*/
void* peek(list l, node n){
    return n->data;
}

/**
 * Returns true iff l contains data.
 * Precondition: l is a valid list.
 * Postcondition: Returns 0 if no node in l
 *   contains data. Otherwise, returns non-zero.
 *   l is unchanged.
 * */
int contains(list l, void *data){
    node next_node = l->head;
    while(next_node!= NULL && next_node->data!=data){
        next_node = next_node->next;
    }
    return next_node!= NULL;
}

/**
 * Returns the node that stores data, or NULL if no such 
 *   node exists.
 * Precondition: l is a valid list.
 * Postcondition: l is unchanged. If contains(l, data) is
 *   true, returns any node storing data. Otherwise, 
 *   returns NULL.*/
node locate(list l, void *data){
    node next_node = l->head;
    while(next_node!= NULL && next_node->data!=data){
        next_node = next_node->next;
    }
    return next_node;
}

/**
 * Returns the node that follows n in l.
 * Precondition: l is a valid list, n returned by
 *  a function in this module when l was a parameter,
 *  no calls to remove since n was returned.
 * Postcondition: Returns the node that follows n in l,
 *   or NULL if n is the last node in l.*/
node next(list l, node n){
    return n->next;
}

/**
 * Returns the node that precedes n in l.
 * Precondition: l is a valid list, n returned by
 *  a function in this module when l was a parameter,
 *  no calls to remove since n was returned.
 * Postcondition: Returns the node that precedes n in l,
 *   or NULL if n is the last node in l.*/
node previous(list l, node n){
    return n->previous;
}

/**
 * Returns the first node in l.
 * Precondition: l is a valid, non-empty list.
 * Postcondition: l is unchanged. Returns the first node
 *   in l.*/
node head(list l){
    return l->head;
}

/**
 * Returns the last node in l.
 * Precondition: l is a valid, non-empty list.
 * Postcondition: l is unchanged. Returns the last node
 *   in l.*/
node tail(list l){
    return l->tail;
}


/**
 * Sorts the nodes in l using the provided cmp function.
 * Precondition: l is a valid, possibly empty list.
 * Postcondition: The contents of l are unchanged, but 
 *   may be in a different order (i.e. if contains(l,d) has
 *   the same value before and after sort, for every d). 
 *   Additionally, for every node n in l,
 *   cmp(peek(l,n), peek(l,next(l,n))) <= 0. */
 
 
//I have created a monster and am proud of it.
//Bubble sort will never RIP as long as lazyness lives.
//She's fast enough..sometimes..every once in a while.

void sort(list l, int (*cmp)(void*, void *)){
    int sorted = 0;
    while((! sorted)&& l->size!=0){
        
        sorted = 1;
        node current_node = l->head;
        node next_node;
        
        while((next_node=current_node->next)!=NULL){
            if ((*cmp) (peek(l,current_node), peek(l,current_node->next)) < 0){
                
                if (l->head == current_node) l->head = next_node;
                if (l->tail == next_node) l->tail = current_node;
                
                if (current_node->previous != NULL) current_node->previous->next = next_node;
                if (next_node->next != NULL) next_node->next->previous = current_node;
                
                current_node->next = next_node->next;
                next_node->previous = current_node->previous;
                
                current_node->previous = next_node;
                next_node->next = current_node;
                
                sorted = 0;
            }
            current_node = next_node;
        }
    }
}


/**
 * Prints information about a list instance
void print_list(list l){
    printf("\nThe address of THE LIST is : %d\n", l);
    printf("Size: %d, Head %d, Tail %d\n", l->size, l->head, l->tail);
    int count = 0;
    node current_node = l->head;
    while (current_node!=NULL){
        printf("%d-Address: %d\n", count++, current_node);
        printf("--Data_Pointer: %d, Data: %d, Previous %d, Next %d\n", current_node->data, *((int*)current_node->data), current_node->previous, current_node->next);
        current_node = current_node->next;
    }
    printf("--------------\n");
    count = 0;
    current_node = l->head;
    while (current_node!=NULL){
        printf("%d |%d|    ", count++, *((int*)current_node->data));
        current_node = current_node->next;
    }
    printf("\n../|Done|\\..\n\n");
}*/