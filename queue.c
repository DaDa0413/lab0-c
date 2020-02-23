#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"
#include "strnatcmp.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    // Dada: If nothing return by malloc, just return NULL
    if (q == NULL) {
        printf("ERROR: q_new() failed\n");
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    printf("INFO: q new success\n");
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    // Dada: Free all the list element and the head of the queue
    if (q == NULL) {
        return;
    }

    list_ele_t *current_ptr = q->head;
    list_ele_t *next = NULL;
    while (current_ptr != NULL) {
        next = current_ptr->next;
        // Dada: Free the memory used by string and list elements
        free(current_ptr->value);
        free(current_ptr);
        current_ptr = next;
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* TODO: What should you do if the q is NULL? */
    if (q == NULL) {
        printf("ERROR: Insert head to a NULL queue\n");
        return false;
    }
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (newh == NULL) {
        // Dada: if queue is allocated at this time
        printf("ERROR: allocate newh fail\n");
        return false;
    }
    unsigned int s_lenth = strlen(s);
    newh->value = malloc(sizeof(char) * (s_lenth + 1));
    // Dada: if fail to allocate space for value
    if (newh->value == NULL) {
        printf("ERROR: allocate newh->value fail\n");
        free(newh);
        // Dada: if queue is allocated at this time
        return false;
    }
    strncpy(newh->value, s, s_lenth);
    newh->value[s_lenth] = '\0';
    // Dada: maintain the queue structure
    newh->next = q->head;
    q->head = newh;
    if (q->size == 0)
        q->tail = newh;
    q->size += 1;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL) {
        printf("ERROR: Insert tail to a NULL queue\n");
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (newh == NULL) {
        return false;
    }
    unsigned int s_lenth = strlen(s);
    newh->value = malloc(sizeof(char) * (s_lenth + 1));
    // Dada: if fail to allocate space for value
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, s_lenth);
    newh->value[s_lenth] = '\0';
    // Dada: maintain the queue structure
    newh->next = NULL;
    if (q->size != 0)
        q->tail->next = newh;
    if (q->size == 0)
        q->head = newh;
    q->tail = newh;
    q->size += 1;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    // NULL queue case and empty queue case
    if (q == NULL || q->head == NULL)
        return false;
    unsigned int s_lenth = strlen(q->head->value);
    if (s_lenth < bufsize) {
        strncpy(sp, q->head->value, s_lenth);
        sp[s_lenth] = '\0';
    } else {
        if (bufsize > 1) {
            strncpy(sp, q->head->value, bufsize - 1);
            sp[bufsize - 1] = '\0';
        } else if (bufsize == 1)
            sp[bufsize - 1] = '\0';
    }
    list_ele_t *tmp = q->head;
    // Dada: maintain queue structure and free removed element
    q->size -= 1;
    q->head = q->head->next;
    if (q->size == 0) {
        q->tail = NULL;
    }
    // Free the popped element and the memeory of string
    free(tmp->value);
    free(tmp);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    // Return the size we take down
    if (q == NULL) {
        printf("ERROR: No size of a NULL queue\n");
        return 0;
    }
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL) {
        printf("ERROR: Reverse a NULL queue\n");
        return;
    }
    list_ele_t *prev_ptr = NULL;
    list_ele_t *current_ptr = q->head;
    list_ele_t *next_ptr = NULL;
    while (current_ptr != NULL) {
        next_ptr = current_ptr->next;
        current_ptr->next = prev_ptr;
        prev_ptr = current_ptr;
        current_ptr = next_ptr;
    }
    // Dada: maintain the queue structure
    list_ele_t *tmp = q->tail;
    q->tail = q->head;
    q->head = tmp;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    // Handling NULL queue
    if (q == NULL) {
        printf("ERROR: q sort a NULL queue\n");
        return;
    }
    // Accroding to ascending order, bubble sort the queue
    list_ele_t *roundend = q->tail;
    while (roundend != q->head) {
        list_ele_t *current = q->head;
        while (current != roundend) {
            /* if current element is bigger than next element
            / then swap the values of the two.
            /
            / Tricky solution: Swap the VALUE instead of LIST ELEMENT,
            / it will reduce several pointer re-assignment into three.
            */
            if (strcmp(current->value, current->next->value) > 0) {
                char *temp;
                temp = current->next->value;
                current->next->value = current->value;
                current->value = temp;
            }
            if (current->next == roundend)
                roundend = current;
            else
                current = current->next;
        }
    }
}
