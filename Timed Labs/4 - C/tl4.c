/**
 * CS 2110 - Spring 2020 - Timed Lab #4
 *
 * @author Saumya Jain
 *
 * tl4.c: Complete the functions!
 */

// Do not add ANY additional includes!!!
#include "tl4.h"

#include "string.h"

///* You should NOT have any global variables. */

/// HINT: C doesn't initialize values for you, so make sure you initialize all
/// variables yourself!

/** deep_copy
 *
 * Creates a new deep-copied list of the original list.
 *
 * If listToCopy is NULL return NULL. For any memory allocations
 * failures your code must not leak memory. This means that if any
 * memory allocation failures occur, before you return NULL, you must destroy
 * the list
 *
 * @param listToCopy A pointer to the struct list structure to make a copy of
 * @return The struct list structure created by copying the old one, or NULL on
 *         failure (includes any of the parameters being null)
 */
struct list *deep_copy(struct list *listToCopy) {
  
  if (listToCopy == NULL) {
    return NULL;
  }

  //creating the list that we will be returning
  struct list *listToReturn;
  if ((listToReturn = malloc(sizeof(struct node))) == NULL) {
    return NULL;
  }
  listToReturn -> head = NULL;

  //establishing pointer to head of listToCopy
  struct node *currToCopy = listToCopy -> head;
  //establishing pointer to a curr node for the list to be returned
  struct node *currToReturn;

  if (currToCopy == NULL) {
    return listToReturn;
  }
  if ((currToReturn = malloc(sizeof(struct node))) == NULL) {
    destroy(listToReturn);
    return NULL;
  }

  //establishing starting properties for the curr node for listToReturn
  currToReturn -> data = NULL;
  currToReturn -> next = NULL;
  

  listToReturn -> head = currToReturn;
  currToReturn -> id = currToCopy -> id;

  // process for copying the data from original list
  char *text;
  if ((text = malloc(sizeof(currToCopy -> data))) == NULL) {
    destroy(listToReturn);
    return NULL;
  }
  currToReturn -> data = strcpy(text, currToCopy -> data);

  // loop for copying until list runs out
  currToCopy = currToCopy -> next;
  while (currToCopy != NULL) {
    struct node *nextNode;
    if ((nextNode = malloc(sizeof(struct node))) == NULL) {
      destroy(listToReturn);
      return NULL;
    }

    currToReturn -> next = nextNode;
    nextNode -> id = currToCopy -> id;
    char *text;
    if ((text = malloc(sizeof(currToCopy -> data))) == NULL) {
      destroy(listToReturn);
      return NULL;
    }
    nextNode -> data = strcpy(text, currToCopy -> data);
    nextNode -> next = NULL;
    currToReturn = nextNode;
    currToCopy = currToCopy -> next;
  }

  return listToReturn;
}

/** Destroy
 *
 * Destroys the entire struct list. This function removes every list node
 * and finally remove the list itself.
 *
 * HINT: remember every malloc needs a respective free
 *
 * @param listToDestroy a pointer to the struct list
 */
void destroy(struct list *listToDestroy) {

  if (listToDestroy == NULL) {
    ;
  } else {
    // Establishing pointers to current node and next node, and initializing current to head node
    struct node *curr = listToDestroy -> head;
    struct node *next;

  // While loop for freeing up the malloced memory for each node (data and the node itself)
    while (curr != NULL) {
      next = curr -> next;
      free(curr -> data);
      free(curr);
      curr = next;
    }

    free(listToDestroy);
  }
}
