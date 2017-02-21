#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

int less(void* aa, void* bb){
    return *(int*)bb-*(int*)aa;
}

/**
 * Prints information about a list instance*/
void print_list(list l){
    printf("\nThe address of THE LIST is : %d\n", l);
    printf("Size: %d, Head %d, Tail %d\n", size(l), head(l), tail(l));
    int count = 0;
    node current_node = head(l);
    while (current_node!=NULL){
        printf("%d-Address: %d\n", count++, current_node);
        printf("--Data_Pointer: %d, Data: %d, Previous %d, Next %d\n", peek(l, current_node), *((int*)peek(l, current_node)), previous(l, current_node), next(l, current_node));
        current_node = next(l, current_node);
    }
    printf("--------------\n");
    count = 0;
    current_node = head(l);
    while (current_node!=NULL){
        printf("%d |%d|    ", count++, *((int*)peek(l, current_node)));
        current_node = next(l, current_node);
    }
    printf("\n../|Done|\\..\n\n");
}

int main(){
    list x = create_list();
    printf("\n+++Test of size: %d, and is_empty: %d\n\n", size(x), is_empty(x));
    int nums[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    int *pa = &nums[0];
    append(x, pa+0);    printf("+++Appending pointer to int 0:");    print_list(x);
    printf("+++Test of size: %d, and is_empty: %d\n\n", size(x), is_empty(x));
    prepend(x, pa+6);    printf("+++Prepending pointer to int 6:");    print_list(x);
    printf("+++Test of size: %d, and is_empty: %d\n\n", size(x), is_empty(x));
    append(x, pa+12);    printf("+++Appending pointer to int 12:");    print_list(x);
    printf("+++Test of size: %d, and is_empty: %d\n\n", size(x), is_empty(x));
    prepend(x, pa+14);    printf("+++Prepending pointer to int 14:");    print_list(x);
    sort(x,*less);    printf("+++Test of sort:");    print_list(x);
    
    printf("\n+++Testing movement and peek functions: \n\n");
    printf("Head: %d, Tail: %d, After Head: %d, After After Head: %d, After After Before Head: %d, Before Tail: %d, Before Before Tail: %d, Before Before After Tail: %d\n\n", 
           head(x), tail(x), next(x, head(x)), next(x, next(x, head(x))), previous(x, next(x, next(x, head(x)))), previous(x, tail(x)), previous(x, previous(x, tail(x))), next(x, previous(x, previous(x, tail(x)))));
    printf("Head Data: %d, Tail Data: %d, After Head Data: %d, After After Head Data: %d, After After Before Head Data: %d, Before Tail Data: %d, Before Before Tail Data: %d, Before Before After Tail Data: %d\n\n", 
           *((int*)peek_front(x)), *((int*)peek_back(x)), *((int*)peek(x, next(x, head(x)))), *((int*)peek(x, next(x, next(x, head(x))))), *((int*)peek(x, previous(x, next(x, next(x, head(x)))))), *((int*)peek(x, previous(x, tail(x)))), *((int*)peek(x, previous(x, previous(x, tail(x))))), *((int*)peek(x, next(x, previous(x, previous(x, tail(x)))))));
    
    printf("\n+++Testing contains and locate functions: \n");
    printf("Contains 6: %d, Where: %d, Value At: %d\n", contains(x, pa+6), locate(x, pa+6), *((int*)peek(x, locate(x, pa+6))));
    printf("Contains 14: %d, Where: %d, Value At: %d\n", contains(x, pa+14), locate(x, pa+14), *((int*)peek(x, locate(x, pa+14))));
    printf("Contains 9: %d\n", contains(x, pa+9));
    
    printf("\n\n+++Appending 11, Prepending 2, and Appending another 6 to make room to test delete functions:");
    append(x, pa+11);    prepend(x, pa+2);    append(x, pa+6);    print_list(x);
    
    printf("\n+++Extra Sort Test:");
    sort(x,*less);    print_list(x);
    
    printf("\n+++Testing remove_data with removing (pointer to position in the array) 6:");
    remove_data(x, pa+6);    print_list(x);
    printf("+++Testing remove_data with removing 0:");
    remove_data(x, pa+0);    print_list(x);
    printf("+++Testing remove_data with removing 9 (not in the list):");
    remove_data(x, pa+9);    print_list(x);
    printf("+++Testing remove_dll (remove) with removing 12:");
    remove_dll(x, locate(x, pa+12));    print_list(x);
    printf("+++Testing remove_dll (remove) with removing 14:");
    remove_dll(x, locate(x, pa+14));    print_list(x);
    printf("+++Testing remove_back:");
    remove_back(x);    print_list(x);
    printf("+++Testing remove_front:");
    remove_front(x);    print_list(x);
    
    printf("\n+++Tested all delete functions with one item in the list:\n\n");
    printf("+++Testing remove_data:");    remove_data(x, pa+6);    print_list(x);    printf("+++Adding node:");    prepend(x, pa+6);    print_list(x);
    printf("+++Testing remove_dll (remove):");    remove_dll(x, locate(x, pa+6));    print_list(x);    printf("+++Adding node:");    prepend(x, pa+6);    print_list(x);
    printf("+++Testing remove_back:");    remove_back(x);    print_list(x);    printf("+++Adding node:");    prepend(x, pa+6);    print_list(x);
    printf("+++Testing remove_front:");    remove_front(x);    print_list(x);    printf("+++Adding node:");    prepend(x, pa+6);    print_list(x);
    
    printf("\n\n+++Testing sort with a one item list:");
    sort(x,*less);    print_list(x);
    remove_front(x);    //print_list(x);
    printf("+++Testing sort with a zero item list:");
    sort(x,*less);    print_list(x);
    printf("+++Testing remove_data with a zero item list:");
    remove_data(x,*less);    print_list(x);
    
    
    //Could not figure out a proper way to test this one since it just messages the malloc thing
    printf("\n+++Destroying List\n\n");
    destroy_list(x);
    
    printf("END");
    return 0;
}
