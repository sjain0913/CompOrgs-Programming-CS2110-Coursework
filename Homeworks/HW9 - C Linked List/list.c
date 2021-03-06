/**
 * CS 2110 - Spring 2020 - Homework #9
 *
 * @author Saumya Jain
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return 1 if
 * the function returns a int).
 */

// Do not add ANY additional includes!!!
#include "list.h"

/* You should NOT have any global variables. */

/* The create_node function is static because this is the only file that should
   have knowledge about the nodes backing the linked List. */
static inline Node *create_node(char *data);

/** create_node
  *
  * Helper function that creates a Node by allocating memory for it on the heap.
  * Be sure to set its next pointer to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @param data a void pointer to data the user wants to store in List
  * @return a Node
  */
static Node* create_node(char *data)
{
  Node *node = (Node *) malloc(sizeof(Node));

  //when malloc returns NULL
  if (node == NULL) {
    return node;
  }

	node -> data = data;
	node -> next = NULL;
  return node;
}

/** create_list
  *
  * Creates a struct linked_list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head and tail to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @return a pointer to a new struct list or NULL on failure
  */

LinkedList *create_list(void)
{
  LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));

  //when malloc returns NULL
  if (list == NULL) {
    return NULL;
  }

  list -> head = NULL;
  list -> size = 0;
  return list;
}

/** push_front
  *
  * Adds the element at the front of the struct linked_list.
  *
  * @param list a pointer to the struct linked_list structure.
  * @param data the data to add to the struct linked_list.
  * @return  1 if the struct linked_list is NULL, 0 if successful,
  */
int push_front(LinkedList *list, char *data)
{
  //returning 1 error code when the list from struct is NULL
  if (list == NULL) {
    return 1;
  }

  //returning 1 error code when the created node is NULL
  Node *node = create_node(data);
  if (node == NULL) {
    return 1;
  }
  
  if (list -> size == 0) {
    list -> head = node;
  }
  else {
    node -> next = list -> head;
    list -> head = node;
  }

  list -> size++;
  return 0;
}

/** push_back
  *
  * Adds the element to the back of the LinkedList.
  *
  * @param list a pointer to the LinkedList structure.
  * @param data the data to add to the LinkedList.
  * @return 1 if the LinkedList is NULL, 0 if successful.
  */
int push_back(LinkedList *list, char *data)
{
  //returning 1 error code when the list from struct is NULL
  if (list == NULL) {
    return 1;
  }

  //returning 1 error code when the created node is NULL
  Node *node = create_node(data);
  if (node == NULL) {
    return 1;
  }

  if (list -> size == 0) {
    list -> head = node;
  }
  Node *temp = list -> head;
  while (temp -> next != NULL) {
    temp = temp -> next;
  }
  temp -> next = node;
  list -> size++;
  return 0;
}

/** add_at_index
  *
  * Add the element at the specified index in the LinkedList. This index must lie in
  * the inclusive range [0,size].
  * For example, if you have no elements in the LinkedList,
  * you should be able to add to index 0 but no further.
  * If you have two elements in the LinkedList,
  * you should be able to add to index 2 but no further.
  *
  * @param list a pointer to the LinkedList structure
  * @param index 0-based, starting from the head in the inclusive range
  *              [0,size]
  * @param data the data to add to the LinkedList
  * @return 1 if the index is out of bounds or the LinkedList is NULL
  *         (do not add the data in this case)
  *         otherwise (on success) return 0
  */
int add_at_index(LinkedList *list, char *data, int index)
{
  //checking if index out of bounds or if list from struct is NULL
  if (list == NULL || index < 0 || index > (list -> size)) {
    return 1;
  }

  //cases when list is empty (add to front) or when we need to add to back
  if ((list -> size) == 0) {
    return push_front(list, data);
  } else if (index == (list -> size)) {
    return push_back(list, data);
  }

  //returning 1 error code when the created node is NULL
  Node *newNode = create_node(data);
  if (newNode == NULL) {
    return 1;
  }

  Node *curr = list -> head;
  //going through linked list to the desired index
  for (int i = 0; i < index - 1; i++) {
    curr = curr -> next;
  }
  newNode -> next = curr -> next;
  curr -> next = newNode;
  list -> size++;
  return 0;
}

/** get
  *
  * Gets the data at the specified index in the LinkedList
  *
  * @param list a pointer to the LinkedList structure
  * @param index 0-based, starting from the head.
  * @param dataOut A pointer to a pointer used to return the data from the
  *        specified index in the LinkedList or NULL on failure.
  * @return 1 if dataOut is NULL or index is out of range of the LinkedList or
  *         the LinkedList is NULL, 0 (on success) otherwise
  */
int get(LinkedList *list, int index, char **dataOut)
{
  //returning 1 error code when the list from struct is NULL or when index out of bounds
  if (list == NULL||index < 0 || index >= (list -> size)|| list -> size == 0) {
    *dataOut = NULL;
    return 1;
  }
  //returning 1 error code when data to be returned is NULL
  if (dataOut == NULL) {
    return 1;
  }

  Node *curr = list -> head;
  //iterating to the desired node
  for (int i = 0; i < index; i++) {
    curr = curr -> next;
  }
  *dataOut = curr -> data;
  return 0;
}

/** contains
  *
  * Traverses the LinkedList, trying to see if the LinkedList contains some
  * data. We say the list contains the data if the data string of the node 
  * matches the node passed in.
  *
  * You may use the string library functions to complete this comparison
  * (see what is included in list.h)
  * 
  * If there are multiple pieces of data in the LinkedList which are equal to
  * the "data" parameter, return the one at the lowest index.
  *
  *
  * @param list a pointer to the LinkedList structure
  * @param data The data, to see if it exists in the LinkedList
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the LinkedList or NULL on failure
  * @return int    0 if dataOut is NULL, the list is NULL, or the list
  *                does not contain data, else 1
  */
int contains(LinkedList *list, char *data, char **dataOut)
{
  //returning 0 if the data out is NULL or if the list from struct is NULL
  if (dataOut == NULL) {
    return 0;
  }
  if (list == NULL) {
    *dataOut = NULL;
    return 0;
  }

  Node *curr = list -> head;
  //keep going until end of linked list reached
  while(curr != NULL) {
    //checking if current node data is the data we need
    if (strcmp(curr -> data, data) == 0) {
      *dataOut = curr -> data;
      return 1;
    }
    curr = curr -> next;
  }
  *dataOut = NULL;
  return 0;
}

/** pop_front
  *
  * Removes the List_node at the front of the LinkedList, and returns its data to the user.
  *
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                List_node or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_front(LinkedList *list, char **dataOut)
{
  //returning error code 1 if data out is nULL or list is NULL (size 0)
  if (dataOut == NULL) {
    return 1;
  }
  if (list == NULL || list -> size == 0) {
    *dataOut = NULL;
    return 1;
  }

  Node *curr = list -> head;
  list -> head = curr -> next;
  *dataOut = curr -> data;
  free(curr);
  list -> size--;
  return 0;
}

/** pop_back
  *
  * Removes the ListNode at the back of the LinkedList, and returns its data to the user
  *
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                ListNode or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_back(LinkedList *list, char **dataOut)
{
  //returning error code 1 if data out is NULL
  if (dataOut == NULL) {
    return 1;
  }
  //returning error code 1 if list is NULL (size = 0)
  if (list == NULL || list -> size == 0) {
    *dataOut = NULL;
    return 1;
  }
  //special scase when list has only 1 node, translates to popping front
  if (list -> size == 1) {
    return pop_front(list, dataOut);
  }

  Node *curr = list -> head;
  //iterating to the node
  while (curr -> next -> next != NULL) {
    curr = curr -> next;
  }
  *dataOut = curr->next->data;
  Node *popped = curr->next;
  curr -> next = NULL;
  free(popped);
  list -> size--;
  return 0;
}


/** remove_at_index
  *
  * Remove the element at the specified index in the LinkedList.
  *
  * @param list a pointer to the LinkedList structure
  * @param index 0-based, starting from the head in the inclusive range
  *              [0,size]
  * @param data the data to remove from the LinkedList
  * @return 1 if the index is out of bounds, the LinkedList is NULL or
  *         the dataOut is NULL
  *         otherwise return 0
  */
int remove_at_index(LinkedList *list, char **dataOut, int index) 
{
  //returning error code 1 if data out is NULL
  if (dataOut == NULL) {
    return 1;
  }
  //returning error code 1 if the list is NULL (size = 0) or if index out of bounds
  if (list == NULL || list -> size == 0 || index < 0 || index > list -> size) {
    dataOut = NULL;
    return 1;
  }

  //special cases for when size is 1 or if index is the last one (pop front and pop back respectively)
  if (list -> size == 1 || index == 0) {
    return pop_front(list, dataOut);
  } else if (index == list -> size - 1)  {
    return pop_back(list, dataOut);
  }

  Node *curr = list -> head;
  for (int i = 0; i <= (index - 2); i++) {
    curr = curr -> next;
  }
  if (curr == NULL || curr -> next == NULL) {
    return 1;
  }
  Node *next = curr -> next -> next;
  *dataOut = curr -> next -> data;
  free(curr -> next);
  list -> size--;
  curr -> next = next;
  return 0;
}

/** empty_list
  *
  * Empties the LinkedList. After this is called, the LinkedList should be
  * empty. This does not free the LinkedList struct itself, just all nodes and
  * data within. Make sure to check that listToEmpty is not NULL before
  * using it.
  *
  * You may call free on a char pointer as well as a node struct pointer.
  *
  * @param list a pointer to the LinkedList structure
  */
void empty_list(LinkedList *list)
{
  if (list == NULL || list -> size == 0) {
    return;
  }

  //freeing up all the nodes to empty list
  Node *curr = list -> head;
  while (curr != NULL) {
    Node *next = curr -> next;
    free(curr -> data);
    free(curr);
    curr = next;
  }

  //resetting size to 0 and head to NULL
  list -> head = NULL;
  list -> size = 0;
}


/** merge_nodes
  *
  *
  * Concatenate the string data in two adjacent nodes (at index and index + 1), 
  * then remove the extra un-merged node. 
  *
  *     LinkedList *A: "CS" -> "2110" -> "Rocks" -> "!" -> NULL
  *
  *     merge_nodes(A, 0): "CS2110" -> "Rocks" -> "!" -> NULL
  *
  * @param list  LinkedList to operate on
  * @param index  Index of the first node to merge
  * @return 1 if the index is out of bounds, or the LinkedList is NULL
  *         otherwise return 0
  */
int merge_nodes(LinkedList *list, int index)
{
  //returning error code 1 if list is NULL (size = 0) or if index out of bounds
  if (list == NULL || list -> size == 0 || index < 0 || index + 1 >= list -> size ) {
    return 1;
  }

  Node *curr = list -> head;
  for (int i = 0; i < index; i++) {
    curr = curr -> next;
  }
  
  Node *temp = create_node(curr -> data);
  temp = malloc(sizeof(curr -> data) + sizeof(curr ->next -> data));
  strcat(temp-> data, curr ->next -> data);

  curr -> data= realloc(curr -> data, sizeof(temp -> data));
  strcpy(curr-> data, temp -> data);
  free(curr ->next -> data);

  char **dataOut = NULL;
  free(curr -> next); 
  remove_at_index(list, dataOut, index + 1);
  list -> size--;
  return 0;
}


