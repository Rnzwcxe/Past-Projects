#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include "bst.h"
//Puts the tree t in alist from smallest to largest
int geta(nodet t, int* alist, int i){
    if (get_right(t)!=NULL){ i = geta(get_right(t), alist, i); }
    alist[i++] = *((int*)get_data(t));
    if (get_left(t) !=NULL){ i = geta(get_left(t), alist, i); }
    return i;
}
//Returns true if tree is ordered properly and has the right child/parent relations
int check_tree(nodet t, int (*cmp)(void*, void *)){
    int temp_right = 1;
    int temp_left = 1;
    if (get_right(t)!=NULL){
        if (! (((*cmp) (get_data(get_right(t)), get_data(t)) >= 0) && (get_parent(get_right(t)) == t))){
            return 0;
        }
        else temp_right = check_tree(get_right(t), (*cmp));
    }
    
    
    if (get_left(t) !=NULL){
        if (! (((*cmp) (get_data(get_left(t)), get_data(t))< 0) && (get_parent(get_left(t)) == t))){
            return 0;
        }
        else temp_left = check_tree(get_left(t), (*cmp));
    }
    
    
    if ((get_right(t)!=NULL) && (get_left(t) !=NULL)) {return 1;}
    //return temp_right || temp_left;
    return temp_right && temp_left;
}

// prints tree sideways
void real_print_tree(nodet t, int depth){
    if (get_right(t)!=NULL){ real_print_tree(get_right(t), depth+1); }
    
    for(int i = 0; i<depth; i++){ printf("    "); }
    //printf("%d",*((int*)get_data(t)));
    printf("%d || %d || %d || %d || %d\n",((int*)get_parent(t)), ((int*)t), *((int*)get_data(t)), ((int*)get_right(t)),((int*)get_left(t)));
    
    if (get_left(t) !=NULL){ real_print_tree(get_left(t) , depth+1); }
}
void print_tree(nodet t){ printf("Format: Parent || Self || Data || Right || Left\n\n");real_print_tree(t, 0); }


int less(void* aa, void* bb){ return *(int*)bb-*(int*)aa; }

int main(){
    srand(time(NULL));
    int nums[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    int *pa = &nums[0];
    //If the testing with high numbers comment out the print trees and to del list in the delete section.
    int size = 50;
    int MaxNum = 90;
    
    printf("+++Creating Tree with Root with 2:\n");
    nodet root = create_tree(pa+2);
    printf("+++Inserting 1:\n");
    insert(root, pa+1, *less);
    printf("+++Inserting 3:\n");
    insert(root, pa+3, *less);
    printf("+++Inserting 2:\n");
    insert(root, pa+2, *less);
    printf("+++Inserting 1:\n");
    insert(root, pa+1, *less);
    print_tree(root);
    printf("\n\n____)()(____:\n");
    printf("+++Delete 2:\n");
    root = delete_tree(root, pa+2, *less);
    print_tree(root);
    printf("\n\n____)()(____:\n");
    printf("+++Delete 3:\n");
    root = delete_tree(root, pa+3, *less);
    print_tree(root);
    printf("\n\n____)()(____:\n");
    printf("+++Delete 1:\n");
    root = delete_tree(root, pa+1, *less);
    print_tree(root);
    printf("\n\n____)()(____:\n");
    printf("+++Delete 2:\n");
    root = delete_tree(root, pa+2, *less);
    print_tree(root);
    printf("\n\n____)()(____:\n");
    printf("+++Delete 1:\n");
    root = delete_tree(root, pa+1, *less);
    printf("--Is root \"NULL\": %d\n", root==NULL);
    
    printf("\n\n");
    printf("---------------------------------------------------------------");
    printf("\n\n\n");
    
    int placeIn[size];
    int *ps = &placeIn[0];
    
    printf("+++Creating a new Tree with Root with a Random Root:\n\n");
    placeIn[0] = rand()%MaxNum;
    root = create_tree(ps+0);
    print_tree(root);
    printf("\n\n____)()(____:\n");
    printf("+++Inserting %d Random Nodes Between 0 and %d:\n\n", size, MaxNum);
    for (int i = 1; i < size; i++){
        placeIn[i] = rand()%MaxNum;
        insert(root, ps+i, *less);
    }
    print_tree(root);
    printf("\n\n____)()(____:\n");
    printf("+++Checking that the Tree is in Order .. %d\n", check_tree(root, *less));
    
    
    printf("\n\n____)()(____:\n");
    printf("+++The Tree as a Sorted List:\n");
    int sortedTree[size];
    geta(root, sortedTree, 0);
    for (int i = 0; i < size; i++){
        printf("%d, ", sortedTree[i]);
    }
    printf("\n\n\n____)()(____:\n");
    printf("+++The Unsorted Values Inserted into the Tree:\n");
    for (int i = 0; i < size; i++){
        printf("%d, ", placeIn[i]);
    }
    
    int boolen = 1;
    for (int i = 0; i < size; i++){
        if ( (!lookup(root, &placeIn[i], *less)) || (*((int*)(get_data(lookupNode(root, &placeIn[i], *less)))) !=  placeIn[i]) ){
            boolen = 0;
        }
    }
    printf("\n\n\n____)()(____:\n");
    printf("+++Checking that all of the Inserted Elements are in the Tree .. %d\n", boolen);
    
    boolen = 1;
    int temp;
    for (int i = 0; i < size; i++){
        temp = sortedTree[i]+rand()%10;
        if ( (sortedTree[i]>temp>sortedTree[i+1])&&(lookup(root, &(temp), *less)) ){
            boolen = 0;
        }
    }
    printf("\n\n____)()(____:\n");
    printf("+++Checking that Items not in the Tree Cannot be Found .. %d\n", boolen);
    
    
    printf("\n\n");
    printf("---------------------------------------------------------------");
    printf("\n\n\n");
    printf("(;_;)\\/(;_;) Preparing to Check Delete:\n\n\n");
    
    boolen = 1;
    int boolen2 = 1;
    int coinFlip = 0;
    nodet toDel;
    int temp2;
    int CopyPlaceIn[size];
    for (int j = 0; j < size; j++){ CopyPlaceIn[j] = placeIn[j]; }
    
    for (int i = 0; i < size; i++){
        temp = rand()%(size-i);
        temp2 = CopyPlaceIn[temp];
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("((((((((((((((((( Deleting: %d, Iteration: %d\n", temp2,i);
        printf("##########################################################\n");
        coinFlip = rand()%2;
        if (coinFlip == 0){ root = delete_tree(root, &temp2, *less); }
        else if (coinFlip == 1) {
                nodet toDel = lookupNode(root, &temp2, *less);
                root = delete_node(root, toDel, &temp2, *less);
        }
        printf("Deleted\n");
        if (root != NULL) {
            print_tree(root);
            printf("\n\n");
            
            if (!check_tree(root, *less)){ boolen = 0; }
            printf("+++Checking that the Tree is in Order .. %d\n", boolen);
            
            printf("+++Checking that the Tree does not Contain %d .. %d\n", temp2, !lookup(root, &temp2, *less));
            
            CopyPlaceIn[temp] = -1;
            for (int j = 0; j < size; j++){
                if ( CopyPlaceIn[temp] != -1 && (!lookup(root, &CopyPlaceIn[j], *less)) )     { boolen2 = 0; }
            }
            printf("+++Checking that the Tree Contains all it Should .. %d\n", boolen);
            
            geta(root, sortedTree, 0);
            for (int j = 0; j < size; j++){
                CopyPlaceIn[j] = sortedTree[j];
            }
            printf("+++The Items Left to Delete:\n");
            for (int j = 0; j < size-i-1; j++){
                printf("%d, ", CopyPlaceIn[j]);
            }
            printf("\n\n\n");
        } else printf("Root is NULL\n");
    }
}