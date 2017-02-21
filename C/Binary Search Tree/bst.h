typedef struct bst_node* nodet;

//Returns a new tree
//Takes the data for the root node
nodet create_tree(void* data);

void* get_data(nodet t);
nodet get_parent(nodet t);
nodet get_left(nodet t);
nodet get_right(nodet t);

//Inserts a new node
void insert(nodet t, void* data, int (*cmp)(void*, void *));
//Returns true if the node is in the tree
int lookup(nodet t, void* data, int (*cmp)(void*, void *));
//Returns the first node with the same data pointer
void* lookupNode(nodet t, void* data, int (*cmp)(void*, void *));
//Deletes the first node with the same data pointer
//Returns the root of the new tree
nodet delete_tree(nodet root, void* data, int (*cmp)(void*, void *));
//Deletes nodet t from the tree defined by root
nodet delete_node(nodet root, nodet t, void* data, int (*cmp)(void*, void *));

//void print_tree(nodet t);