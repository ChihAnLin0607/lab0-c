/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;
    list_ele_t *curr = q->head, *next;
    while (curr) {
        next = curr->next;
        free(curr->value);
        free(curr);
        curr = next;
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    size_t s_size;

    // Return false if q is NULL
    if (!q)
        return false;

    // Allocate a new list_elet_t
    newh = malloc(sizeof(list_ele_t));
    if (!newh)  // Return false if malloc fail;
        return false;

    // Allocate the space for the string, and then copy s into it
    s_size = strlen(s);
    newh->value = malloc(s_size + 1);  // "+1" is for the last charactor '\0'
    if (!newh->value) {
        free(newh);
        return false;
    }
    memcpy(newh->value, s, s_size);
    newh->value[s_size] = 0;

    // Insert the new list_ele_t into q
    if (!q->head)
        q->tail = newh;
    newh->next = q->head;
    q->head = newh;
    q->size++;
    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    list_ele_t *newh;
    size_t s_size;

    // Return false if q is NULL
    if (!q)
        return false;

    // Allocate a new list_elet_t
    newh = malloc(sizeof(list_ele_t));
    if (!newh)  // Return false if malloc fail;
        return false;

    // Allocate the space for the string, and then copy s into it
    s_size = strlen(s);
    newh->value = malloc(s_size + 1);  // "+1" is for the last charactor '\0'
    if (!newh->value) {
        free(newh);
        return false;
    }
    memcpy(newh->value, s, s_size);
    newh->value[s_size] = 0;

    // Insert the new list_ele_t into q
    if (!q->head)
        q->head = newh;
    if (q->tail)
        q->tail->next = newh;
    q->tail = newh;
    newh->next = NULL;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (!q || !q->head)
        return false;
    if (sp) {
        size_t cp_size = (strlen(q->head->value) >= bufsize - 1)
                             ? bufsize - 1
                             : strlen(q->head->value);
        memcpy(sp, q->head->value, cp_size);
        sp[cp_size] = 0;
    }

    list_ele_t *new_head;
    new_head = q->head->next;
    if (!new_head)
        q->tail = NULL;

    free(q->head->value);
    free(q->head);

    q->head = new_head;
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
        return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (!q || !q->size || q->size == 1)
        return;

    list_ele_t *prev = q->head, *curr = q->head->next, *next;

    q->head->next = NULL;
    q->tail = q->head;

    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    q->head = prev;

    return;
}
