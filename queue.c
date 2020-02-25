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
    // If nothing return by malloc, just return NULL
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
    // Free all the list element and the head of the queue
    if (q == NULL) {
        return;
    }

    list_ele_t *current_ptr = q->head;
    list_ele_t *next = NULL;
    while (current_ptr != NULL) {
        next = current_ptr->next;
        // Free the memory used by string and list elements
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
    if (newh == NULL) {
        // If queue is allocated at this time
        printf("ERROR: allocate newh fail\n");
        return false;
    }
    unsigned int s_lenth = strlen(s);
    newh->value = malloc(sizeof(char) * (s_lenth + 1));
    // If fail to allocate space for value
    if (newh->value == NULL) {
        printf("ERROR: allocate newh->value fail\n");
        free(newh);
        // If queue is allocated at this time
        return false;
    }
    strncpy(newh->value, s, s_lenth);
    newh->value[s_lenth] = '\0';
    // Maintain the queue structure
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
    if (q == NULL) {
        printf("ERROR: Insert tail to a NULL queue\n");
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }
    unsigned int s_lenth = strlen(s);
    newh->value = malloc(sizeof(char) * (s_lenth + 1));
    // If fail to allocate space for value
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, s_lenth);
    newh->value[s_lenth] = '\0';
    // Maintain the queue structure
    newh->next = NULL;
    if (q->size != 0)
        q->tail->next = newh;
    if (q->size == 0)
        q->head = newh;
    q->tail = newh;
    q->size += 1;
    return true;
}

/* Insert a existed list element into queue
 * Return true if success
 * Return false if insert element to a NULL queue
 */
bool q_insert_element_to_tail(queue_t *q, list_ele_t *ele)
{
    if (q == NULL) {
        printf("ERROR: Insert a list element to tailto a NULL queue\n");
        return false;
    }
    // Maintain the queue structure
    ele->next = NULL;
    if (q->size != 0)
        q->tail->next = ele;
    if (q->size == 0)
        q->head = ele;
    q->tail = ele;
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
    // Maintain queue structure and free removed element
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
    // Return the queue size we take down
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
    // Maintain the queue structure
    list_ele_t *tmp = q->tail;
    q->tail = q->head;
    q->head = tmp;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
// new q_sort with merge sort
void q_sort(queue_t *q)
{
    if (q == NULL || q_size(q) == 0 || q_size(q) == 1)
        return;
    // In order to avoid to extra line to handle head element
    // case, we maintain a pseudo head.
    list_ele_t pseudo;
    pseudo.next = q->head;
    for (unsigned int interval = 1; interval < q_size(q); interval *= 2) {
        // prv is the last element of previous round
        // nxt is the first element of next round
        // next_prv will record where prv will move to
        list_ele_t *prv = &pseudo;
        list_ele_t *nxt = pseudo.next;
        while (nxt != NULL) {
            // cur1 and cur2 lead two lists to be sorted
            list_ele_t *cur1 = prv->next;
            list_ele_t *cur2 = cur1;
            for (unsigned int i = 0; cur2 != NULL && i < interval; ++i)
                cur2 = cur2->next;

            // move next_prv and nxt to correct place
            nxt = cur2;
            for (unsigned int i = 0; nxt != NULL && i < interval; ++i)
                nxt = nxt->next;

            queue_t merge = {.head = NULL, .tail = NULL, .size = 0};
            // cur1_end and cur2_end is the next element of each list
            list_ele_t *cur1_end = cur2;
            list_ele_t *cur2_end = nxt;
            while (cur1 != cur1_end || cur2 != cur2_end) {
                if (cur2 == cur2_end ||
                    (cur1 != cur1_end &&
                     strnatcmp(cur1->value, cur2->value) < 0)) {
                    list_ele_t *tmp1 = cur1;
                    cur1 = cur1->next;
                    q_insert_element_to_tail(&merge, tmp1);
                } else {
                    list_ele_t *tmp2 = cur2;
                    cur2 = cur2->next;
                    q_insert_element_to_tail(&merge, tmp2);
                }
            }
            prv->next = merge.head;
            prv = merge.tail;
            merge.tail->next = nxt;
            q->tail = merge.tail;
        }
    }
    q->head = pseudo.next;
}