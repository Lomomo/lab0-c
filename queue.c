#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head) {
        return NULL;
    }
    INIT_LIST_HEAD(head);
    return head;
}

void q_free_element(element_t *entry)
{
    free(entry->value);
    free(entry);
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (!l) {
        return;
    }

    element_t *entry, *safe;
    list_for_each_entry_safe (entry, safe, l, list) {
        q_free_element(entry);
    }
    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head) {
        return false;
    }

    element_t *e = malloc(sizeof(element_t));
    if (!e) {
        return false;
    }

    e->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (!e->value) {
        free(e);
        return false;
    }
    strncpy(e->value, s, strlen(s));
    e->value[strlen(s)] = '\0';

    list_add(&e->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head) {
        return false;
    }

    element_t *e = malloc(sizeof(element_t));
    if (!e) {
        return false;
    }

    e->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (!e->value) {
        free(e);
        return false;
    }
    strncpy(e->value, s, strlen(s));
    e->value[strlen(s)] = '\0';

    list_add_tail(&e->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    element_t *e = list_first_entry(head, element_t, list);
    int str_size =
        strlen(e->value) > bufsize - 1 ? bufsize - 1 : strlen(e->value);
    strncpy(sp, e->value, str_size);
    sp[str_size] = '\0';

    list_del_init(head->next);
    return e;
}


/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    element_t *e = list_last_entry(head, element_t, list);
    int str_size =
        strlen(e->value) > bufsize - 1 ? bufsize - 1 : strlen(e->value);
    strncpy(sp, e->value, str_size);
    sp[str_size] = '\0';

    list_del_init(head->prev);
    return e;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head)) {
        return 0;
    }

    int nums = 0;
    struct list_head *node;
    list_for_each (node, head) {
        nums++;
    }
    return nums;
}

struct list_head *list_get_mid_node(struct list_head *head)
{
    struct list_head *fast = head->next;
    struct list_head *slow = head->next;

    for (; fast != head && fast->next != head; fast = fast->next->next) {
        slow = slow->next;
    }

    return slow;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (!head || list_empty(head)) {
        return false;
    }

    struct list_head *node = list_get_mid_node(head);
    list_del_init(node);
    q_free_element(list_entry(node, element_t, list));
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    if (!head) {
        return;
    }

    struct list_head *node;
    list_for_each (node, head) {
        if (node->next != head) {
            list_move(node, node->next);
        }
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head)) {
        return;
    }
    struct list_head *node, *safe;
    list_for_each_safe (node, safe, head) {
        node->next = node->prev;
        node->prev = safe;
    }
    head->next = head->prev;
    head->prev = node->next;
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
