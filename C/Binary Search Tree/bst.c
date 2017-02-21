#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

struct bst_node{
    void *data;
    nodet parent;
    nodet left;
    nodet right;
            };

//Returns a new tree
//Takes the data for the root node
nodet create_tree(void* data){
    nodet temp = malloc(sizeof(struct bst_node));
    temp->data = data;
    temp->parent = NULL;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void* get_data(nodet t){ return t->data; }
nodet get_parent(nodet t){ return t->parent; }
nodet get_left(nodet t){ return t->left; }
nodet get_right(nodet t){ return t->right; }

//Inserts a new node         
void insert(nodet t, void* data, int (*cmp)(void*, void *)){
    if ((*cmp) (data, t->data) < 0){
        if (t->left == NULL){
            nodet temp = malloc(sizeof(struct bst_node));
            temp->data = data;
            temp->parent = t;
            temp->left = NULL;
            temp->right = NULL;
            t->left  = temp;
            return;
        }
        else insert(t->left, data,(*cmp));
    }
    else{
        if (t->right == NULL){
            nodet temp = malloc(sizeof(struct bst_node));
            temp->data = data;
            temp->parent = t;
            temp->left = NULL;
            temp->right = NULL;
            t->right  = temp;
            return;
        }
        else insert(t->right, data,(*cmp));
    }
}

/*void real_print_tree(nodet t, int depth){
    // prints tree sideways
    if (t->right!=NULL){
        real_print_tree(t->right, depth+1);
    }
    for(int i = 0; i<depth; i++){
    printf("    ");
    }
    printf("%d",*((int*)t->data));
    printf("\n");
    if (t->left !=NULL){
        real_print_tree(t->left , depth+1);
    }
}
void print_tree(nodet t){
        real_print_tree(t, 0);
}*/

//Returns true if the node is in the tree
int lookup(nodet t, void* data, int (*cmp)(void*, void *)){
    if ((*cmp) (t->data, data)==0){ return 1; }
    else{
        if ((*cmp) (data, t->data) < 0){
            if (t->left == NULL){ return 0; }
            else return lookup(t->left ,data,(*cmp));
        }
        else{
            if (t->right == NULL){ return 0; }
            else return lookup(t->right,data,(*cmp));
        }
    }
}

//Returns the first node with the same data pointer
void* lookupNode(nodet t, void* data, int (*cmp)(void*, void *)){
    if ((*cmp) (t->data, data)==0){ return t; }
    else{
        if ((*cmp) (data, t->data) < 0){
            if (t->left == NULL){ return NULL; }
            return lookupNode(t->left ,data,(*cmp));
        }
        else{
            if (t->right == NULL){ return NULL; }
            return lookupNode(t->right,data,(*cmp));
        }
    }
}

//Internal Function
void* find_most_left(nodet t, int (*cmp)(void*, void *)){
    if (t->left == NULL){ return t; }
    else{ return find_most_left(t->left,(*cmp)); }
}

//Deletes nodet t from the tree defined by root
nodet delete_node(nodet root, nodet t, void* data, int (*cmp)(void*, void *)){
    if (t == NULL){
        return root;
    }
    
    //temp is the node to replace t
    nodet temp;
    //will become temp->right
    nodet tempRight;
    //will become temp->left
    nodet tempLeft;
    
    //case for no children
    if (t->left == NULL && t->right == NULL){
        temp = NULL;
    }
    
    //cases for one child
    else if (t->left == NULL && t->right != NULL){ 
        temp = t->right;
    }
    else if (t->right == NULL && t->left != NULL){
        temp = t->left;
    }
    //case for two children
    else if (t->right != NULL && t->left != NULL){
        
        temp = find_most_left(t->right, (*cmp));
        
        //case for if temp is a child of t
        if (temp == t->right){
            tempRight = temp->right;
        }
        //case for if temp is not a child of t
        else{
            tempRight = t->right;
            //----------------------
            if (t->right!=NULL) t->right->parent = temp;
            //----------------------
            
            //----------------------
            if (temp->right!=NULL) temp->right->parent = temp->parent;
            //----------------------
            
            temp->parent->left = temp->right;
            
        }
        tempLeft = t->left;
        //----------------------
        t->left->parent = temp;
        //----------------------
    }
    
    
    //cases with two children; moving temp
    if (t->left!=NULL && t->right!=NULL){
        temp->left = tempLeft;
        temp->right = tempRight;
        //case of if root is being deleted
        if (t->parent == NULL){
            root = temp;
            //Was going to make it not need to return anything but it would not work for trees of one
            //*root = *temp;
            
            //----------------------
            if (temp!=NULL) temp->parent = NULL;
            //----------------------
        }
        else if (t == t->parent->left){
            t->parent->left = temp;
            
            //----------------------
            if (temp!=NULL) temp->parent = t->parent;
            //----------------------
        }
        else{
            t->parent->right = temp;
            
            //----------------------
            if (temp!=NULL) temp->parent = t->parent;
            //----------------------
        }
    }
    //case of no or one child; moving temp
    else{
        if (t->parent == NULL){
            root = temp;
            //Was going to make it not need to return anything but it would not work for trees of one
            //*root = *temp;
            
            //----------------------
            if (temp!=NULL) temp->parent = NULL;
            //----------------------
        }
        else if (t == t->parent->left){
            t->parent->left = temp;
            
            //----------------------
            if (temp!=NULL) temp->parent = t->parent;
            //----------------------
        }
        else{
            t->parent->right = temp;
            
            //----------------------
            if (temp!=NULL) temp->parent = t->parent;
            //----------------------
        }
    }
    free(t);
    return root;
}

//Deletes the first node with the same data pointer
//Returns the root of the new tree
nodet delete_tree(nodet root, void* data, int (*cmp)(void*, void *)){
    nodet t = lookupNode(root,data,(*cmp));
    delete_node(root, t, data, (*cmp));
}