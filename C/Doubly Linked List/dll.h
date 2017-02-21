

//You are responsable for defining the dll
//  and dll_node structures.
typedef struct dll* list;
typedef struct dll_node* node;

/**
 * Returns a new (empty) list.
 * You can define what an empty list is.
 * Precondition: There exists system memory to allocate
 *   a new empty dll structure.
 * Postcondition: A pointer to an empty list is returned.
 *   The returned list is a valid list.*/
list create_list();

/**
 * Frees all memory associated with the given list.
 * Precondition: l is a (possibly empty) list, that was
 *   originally produced with a call to the create_list
 *   function, and l has not already been freed.
 * Postcondition: l and all nodes contained within l are
 *   freed. Data contained within l is not freed.
 *   l is no longer a valid list.*/
void destroy_list(list l);

/**
 * Returns the number of elements in the current list
 * Precondition: l is a valid list.
 * Postcondition: the number of elements in l is returned*/
int size(list l);

/**
 * Returns whether or not the list is empty.
 * Precondition: l is a valid list.
 * Postcondition: Returns 0 iff l is empty.*/
int is_empty(list l);

/*
 * Appends data to l.
 * Precondition: l is a valid list.
 * Postcondition: l now contains a node that stores data.
 *   The size of l is now one larger.
 *   The new node is stored at the end of the list. */
void append(list l, void *data);

/*
 * Prepends data to l.
 * Precondition: l is a valid list.
 * Postcondition: l now contains a node that stores data.
 *   The size of l is now one larger.
 *   The new node is stored at the start of the list. */
void prepend(list l, void *data);

/*
 * Removes the first node from l.
 * Precondition: l is a valid list, and size(l) >= 1.
 * Postcondition: l now contains one less node.
 *   The node at the start of the list was removed.
 *   If size(l) was 1, the list is now empty.*/
void* remove_front(list l);

/*
 * Removes the first node from l.
 * Precondition: l is a valid list, and size(l) >= 1.
 * Postcondition: l now contains one less node.
 *   The node at the end of the list was removed.
 *   If size(l) was 1, the list is now empty.*/
void* remove_back(list l);

/*
 * Removes the first node from l containing data.
 * Precondition: l is a valid list, maybe empty.
 * Postcondition:  If data is in l, the node containing
 *   data that is nearest to the front of the list is 
 *   removed, and a non-zero value is returned. Otherwise,
 *   l is unchanged and 0 is returned.
 *   l is now one element smaller iff data was removed.
 *   If size(l) was 1, and data was removed, l is empty.*/
int remove_data(list l, void *data);

/*
 * Removes n from l.
 * Precondition: l is a valid list, and n was returned by
 *   one of the other functions in this module when l was
 *   the input list to that function, and no remove
 *   functions have been called since n was returned.
 * Postcondition: n is removed from l.
 *   l is now one element smaller.
 *   If size(l) was 1, l is now empty.*/
void remove_dll(list l, node n);

/**
 * Returns the data from the node at the front of l.
 * Precondition: l is not empty.
 * Postcondition: Returns the data stored in the node
 *  at the front of l, l is unchanged.*/
void* peek_front(list l);

/**
 * Returns the data from the node at the back of l.
 * Precondition: l is not empty.
 * Postcondition: Returns the data stored in the node
 *  at the back of l, l is unchanged.*/
void* peek_back(list l);

/**
 * Returns the data from n.
 * Precondition: l is not empty. n was returned by a call
 *   to one of the functions in this module, with l as the
 *   list argument. No calls to remove functions have been
 *   made since n was returned.
 * Postcondition: Returns the data stored in n.
 *  l is unchanged.*/
void* peek(list l, node n);

/**
 * Returns true iff l contains data.
 * Precondition: l is a valid list.
 * Postcondition: Returns 0 if no node in l
 *   contains data. Otherwise, returns non-zero.
 *   l is unchanged.
 * */
int contains(list l, void *data);

/**
 * Returns the node that stores data, or NULL if no such 
 *   node exists.
 * Precondition: l is a valid list.
 * Postcondition: l is unchanged. If contains(l, data) is
 *   true, returns any node storing data. Otherwise, 
 *   returns NULL.*/
node locate(list l, void *data);

/**
 * Returns the node that follows n in l.
 * Precondition: l is a valid list, n returned by
 *  a function in this module when l was a parameter,
 *  no calls to remove since n was returned.
 * Postcondition: Returns the node that follows n in l,
 *   or NULL if n is the last node in l.*/
node next(list l, node n);

/**
 * Returns the node that precedes n in l.
 * Precondition: l is a valid list, n returned by
 *  a function in this module when l was a parameter,
 *  no calls to remove since n was returned.
 * Postcondition: Returns the node that precedes n in l,
 *   or NULL if n is the last node in l.*/
node previous(list l, node n);

/**
 * Returns the first node in l.
 * Precondition: l is a valid, non-empty list.
 * Postcondition: l is unchanged. Returns the first node
 *   in l.*/
node head(list l);

/**
 * Returns the last node in l.
 * Precondition: l is a valid, non-empty list.
 * Postcondition: l is unchanged. Returns the last node
 *   in l.*/
node tail(list l);


/**
 * Sorts the nodes in l using the provided cmp function.
 * Precondition: l is a valid, possibly empty list.
 * Postcondition: The contents of l are unchanged, but 
 *   may be in a different order (i.e. if contains(l,d) has
 *   the same value before and after sort, for every d). 
 *   Additionally, for every node n in l,
 *   cmp(peek(l,n), peek(l,next(l,n))) <= 0. */
void sort(list l, int (*cmp)(void*, void *));



//void print_list(list l);