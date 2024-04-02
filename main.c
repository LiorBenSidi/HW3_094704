#include <stdio.h>
#include "stdlib.h"

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} node_t; // represents a bidirectional node, for using at Traverse linked list

typedef struct {
    node_t *head;
    int size;
} Set; // represents a set in math

/* This function is a helping function that used to insert a node at the end of
 * the linked-list. */
void insert_at_end(int data, node_t *head) {
    // create a link
    node_t *lk = (node_t*) malloc(sizeof(node_t));
    lk->data = data;
    node_t *linked_list = head;
    // point it to old first node
    while (linked_list->next != NULL) {
        linked_list = linked_list->next;
    }
    //point first to new first node
    linked_list->next = lk;
}

/* This function gets the address of two instances of sets,
 * prints each one of them,
 * and returns a new set(using "set_init") of the union of them. */
Set* set_union(Set *a, Set *b) {
}

/* This function gets the address of two instances of sets,
 * prints each one of them,
 * and returns the intersect of them,
 * while the returned set must be one of the given sets(in place). */
Set* set_intersect(Set *a, Set *b) {

}

/* This function gets the address of two instances of sets,
 * prints each one of them,
 * and returns the intersect of them,
 * while the returned set can be one of the given sets(in place),
 * or a new set. */
Set* set_diff(Set *a, Set *b) {

}

/* This function is used for the creation of set s, using memory allocation,
 * and placement the members of the set of the given array. */
void set_init(Set *s, int v[], int num_elements_in_v) {
    // Dynamically allocate memory using malloc()
    s->head = (node_t *) malloc(sizeof(node_t));
    for (int i = 0; i < num_elements_in_v; i++) {
        insert_at_end(v[i], s->head);
    }
}

/* This function is used for print the members of the set s, according to the
 * order of the nodes in the linked-list.
 * Also, used any time we are creating a new set. */
void set_print(Set *s) {
    printf("{ ");
    node_t *linked_list = s->head;
    while (linked_list->next != NULL) {
        printf("%d ", linked_list->data);
        linked_list = linked_list->next;
    }
    printf("}");
}

int main() {
    return 0;
}
