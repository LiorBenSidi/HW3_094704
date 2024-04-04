#include <stdio.h>
#include "stdlib.h"

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} node_t; // struct that represents a node, for using at doubly linked-list

typedef struct {
    node_t *head;
    int size;
} Set; // struct that represents a set in math

/* This function is a helping function that used to insert a node at the end of
 * the linked-list. similar implementation to the function we have already
 * seen at the tutorial */
void insert_at_end(int data, node_t *head) {
    // Dynamically allocate memory for a new pointer to node
    node_t *lk = (node_t*) malloc(sizeof(node_t));
    // Check if memory allocation was successful
    if (lk == NULL) {
        printf("Error: Out of Memory\n");
        return;
    } else { // Memory allocation was successful
        printf("Memory allocated successfully\n");
    }

    // Initialize the "data" attribute of the node according to the given data
    lk->data = data;
    // Initialize the "next" attribute of the node to NULL at first
    lk->next = NULL;

    // initialize a pointer to the node that "head" is point to
    node_t *linked_list = head;

    // iterates over the nodes in the linked-list that "head" is the pointer to,
    // till we get that the "next" attribute is NULL, so we have reached the
    // end of the linked-list
    while (linked_list->next != NULL) {
        // gets the next node in the linked-list
        linked_list = linked_list->next;
    }

    // sets the "next" attribute of the former last node to the new node
    linked_list->next = lk;
    // sets the "prev" attribute of the new node to the former last node
    lk->prev = linked_list;
}

/* This function is used to check if there is already a node with the same data
 * we asked to enter to the Set s, in the linked-list that represents the Set s
 */
int is_exist_already(Set *s, int data) {
    // initialize a pointer to the node that "head" is point to
    node_t *lk = s->head;
    // gets the address of the node that is next to the first node
    lk = lk->next;

    // while the "next" attribute of the current node is not point to NULL,
    // so there is another node to check if ut has the same data as the given
    // data. if we get that the "next" attribute is NULL, so we have reached the
    // end of the linked-list
    while (lk != NULL) {
        if (lk->data == data) {
            // indication to that we have found a node with the same data,
            // so we acknowledge that by retuning 1(that represents true)
            return 1;
        }
        // gets the next node in the linked-list
        lk = lk->next;
    }
    // if we have reached the end of the linked-list, so it means that we have
    // not found a node with the same data, and acknowledge that by returning 0
    return 0;
}

/* This function is used for the creation of set s, using memory allocation,
 * and placement the members of the set of the given array. */
void set_init(Set *s, int v[], int num_elements_in_v) {
    if (s == NULL) { // Handle the case when the given pointer is point to NULL
        printf("Error: the given pointer is point to NULL\n");
        return;
    }

    // Dynamically allocate memory for the new head "attribute" in Set s
    s->head = (node_t*) malloc(sizeof(node_t));
    if (s->head == NULL) {
        printf("Error: Out of Memory\n");
        return;
    } else { // Memory allocation was successful
        printf("Memory allocated successfully\n");
    }

    // Initialize the prev pointer of the head node to NULL
    s->head->prev = NULL;

    if (num_elements_in_v == 0) { // Handle the case when the given array is empty
        s->head->next = NULL;
        s->size = 0;
        return;
    }

    // Initialize the next pointer of the node that "head" is point to, to NULL
    s->head->next = NULL;
    s->size = 0;

    // iterates over the elements in the given array,
    // check if there is already a node with the same data using helping
    // function "is_exist_already",
    // and rise the "size" attribute of the "Set" instance by 1 after each
    // successful adding of node, using a variation of a function that we have
    // already seen at the tutorial
    for (int i = 0; i < num_elements_in_v; i++) {
        if (!is_exist_already(s,v[i])) {
            insert_at_end(v[i], s->head);
            s->size++;
        }
    }
}

/* This function is used for print the members of the set s, according to the
 * order of the nodes in the linked-list.
 * Also, used any time we are creating a new set. */
void set_print(Set *s) {
    if (s == NULL) { // Handle the case when the given pointer is point to NULL
        printf("Error: the given pointer is point to NULL\n");
        return;
    } else if (s->size == 0) { // check if the given Set is empty
        printf("{ }\n");
        return;
    } else if (s->head == NULL) {
        printf("Error: The 'head' attribute is point to NULL\n");
        return;
    }

    printf("{ ");

    // in order to check that the elements of the given Set is not include
    // duplicates, we are using two pointers, that we will use in order to
    // compare the current node with all nodes that will come after

    // initialize a flag to acknowledge existence of duplicate
    int flag_duplicate = 0;
    // initialize a pointer to the node that "head" is point to
    node_t *current = s->head;
    // gets the address of the node that is next to the first node
    current = current->next;
    // initialize another pointer, that we will be using to check duplicates
    node_t *check_if_duplicate;

    // while the "next" attribute of the current node is not point to NULL
    while (current != NULL) {
        // sets the flag to 0 at each iteration
        flag_duplicate = 0;
        // gets the node that the current node is point to
        check_if_duplicate = current->next;
        // while the both condition is existing:
        // 1. We have not reached the end of the link list
        // 2. We have not found a duplicate already
        while (check_if_duplicate != NULL && flag_duplicate != 1) {
            // checks for the duplication in the "data" attribute
            if (current->data == check_if_duplicate->data) {
                // if so, acknowledge that by change the flag
                flag_duplicate = 1;
            }
            // gets the next node to check
            check_if_duplicate = check_if_duplicate->next;
        }

        // if we have not found a duplicate of the current node, prints its data
        if (!flag_duplicate) {
            printf("%d", current->data);
            if (current->next != NULL) {
                printf(", ");
            }
        }

        // gets the next node
        current = current->next;
    }

    printf(" }\n");
}

// Helper function that used check if the given element is in the array already
int is_element_in_array(int element, int *array, int array_size) {
    // iterates over the array, and if we have found a duplicate, we return 1
    // to acknowledge that. If we have reached the end of the array, return 0
    int i = 0;
    while (i < array_size) {
        if (array[i] == element) {
            return 1;
        }
        i++;
    }
    return 0;
}


/* This function gets the address of two instances of sets,
 * prints each one of them,
 * and returns a new set(using "set_init") of the union of them. */
Set* set_union(Set *a, Set *b) {
    // checks if one or both of the given sets are NULL
    if (a == NULL && b == NULL) {
        printf("Error: both sets are NULL.\n");
    } else if (a == NULL) {
        printf("Error: set a is NULL.\n");
    } else if (b == NULL) {
        printf("Error: set b is NULL.\n");
    }

    // Print the sets
    printf("Set a: ");
    set_print(a);
    printf("Set b: ");
    set_print(b);

    // Allocate memory for a temporary array that we will send to "set_init"
    int *temp = (int *)malloc(sizeof(int) * (a->size + b->size));

    // Check if memory allocation was successful
    if (temp == NULL) {
        printf("Error: Out of Memory\n");
        return NULL; // Memory allocation failed
    } else { // Memory allocation was successful
        printf("Memory allocated successfully\n");
    }

    // Initialize a counter to know the number of unique elements
    int count = 0;

    // initialize a pointer to the node that "head" is point to in Set a
    node_t *current = a->head;
    // gets the address of the node that is next to the first node
    current = current->next;
    // while the "next" attribute of the current node is not point to NULL
    while (current != NULL) {
        // checks for duplicates
        if (!is_element_in_array(current->data, temp, count)) {
            // adds the "data" of the current node to the cell at index count
            temp[count] = current->data;
            count++;
        }
        // gets the address of the node that is next to the current node
        current = current->next;
    }

    // initialize a pointer to the node that "head" is point to in Set a
    current = b->head;
    // gets the address of the node that is next to the first node
    current = current->next;
    // while the "next" attribute of the current node is not point to NULL
    while (current != NULL) {
        // checks for duplicates
        if (!is_element_in_array(current->data, temp, count)) {
            // adds the "data" of the current node to the cell at index count
            temp[count] = current->data;
            count++;
        }
        // gets the address of the node that is next to the current node
        current = current->next;
    }

    // Allocate memory for a Set that we will send to set_init
    Set *union_set = (Set *)malloc(sizeof(Set));
    // Check if memory allocation was successful
    if (union_set == NULL) {
        // before exist, free the memory of "temp"
        free(temp);
        printf("Error: Out of Memory\n");
    } else { // Memory allocation was successful
        printf("Memory allocated successfully\n");
    }

    // Creates the union Set, using "set_int"
    set_init(union_set, temp, count);

    // before exist, free the memory of "temp"
    free(temp);

    // Return a pointer to the union Set
    return union_set;
}

/* This function gets the address of two instances of sets,
 * prints each one of them,
 * and returns the intersect of them,
 * while the returned set must be one of the given sets(in place). */
Set* set_intersect(Set *a, Set *b) {
    // checks if one or both of the given sets are NULL
    if (a == NULL && b == NULL) {
        printf("Error: both sets are NULL.\n");
    } else if (a == NULL) {
        printf("Error: set a is NULL.\n");
    } else if (b == NULL) {
        printf("Error: set b is NULL.\n");
    }

    // Print the sets
    printf("Set a: ");
    set_print(a);
    printf("Set b: ");
    set_print(b);

    // we have chosen to use Set a, as the Set that will store the intersect
    Set *result_set = a;
    // initialize a pointer to the node that "head" is point to in Set a
    node_t *current = result_set->head;
    // gets the address of the node that is next to the first node
    current = current->next;
    // initialize a pointer to the "head" attribute,
    // and we can use a "prev" variable cause the node struct we have build is
    // a doubly linked-list
    node_t *prev = result_set->head;


    // while the "next" attribute of the current node is not point to NULL
    while (current != NULL) {
        // checks if the current element is not in Set b
        if (!is_exist_already(b, current->data)) {
            // if the data is not in Set a, remove it from Set a
            prev->next = current->next;
            if (current->next != NULL) {
                current->next->prev = prev;
            }
            // move to the next node
            current = current->next;
            // decrease the size if the intersect by 1
            result_set->size--;
        } else {
            // if the current node in Set a, have a data that is already in
            // set b, move to the next node
            prev = current;
            current = current->next;
        }
    }

    // Return a pointer to the intersect Set
    return result_set;
}

/* This function gets the address of two instances of sets,
 * prints each one of them,
 * and returns the difference a/b,
 * while the returned set can be one of the given sets(in place),
 * or a new set. */
Set* set_diff(Set *a, Set *b) {
    // checks if one or both of the given sets are NULL
    if (a == NULL && b == NULL) {
        printf("Error: both sets are NULL.\n");
    } else if (a == NULL) {
        printf("Error: set a is NULL.\n");
    } else if (b == NULL) {
        printf("Error: set b is NULL.\n");
    }

    // Print the sets
    printf("Set a: ");
    set_print(a);
    printf("Set b: ");
    set_print(b);

    // initialize a pointer to the node that "head" is point to in Set a
    node_t *current = a->head;
    // gets the address of the node that is next to the first node
    current = current->next;
    // initialize a pointer to the "head" attribute,
    // and we can use a "prev" variable cause the node struct we have build is
    // a doubly linked-list
    node_t *prev = a->head;

    // while the "next" attribute of the current node is not point to NULL
    while (current != NULL) {
        // checks if the current element is in Set b
        if (is_exist_already(b, current->data)) {
            // if the data is in Set b, we should remove it from Set a
            prev->next = current->next;
            if (current->next != NULL) {
                current->next->prev = prev;
            }
            // move to the next node
            current = current->next;
            // decrease the size if the difference by 1
            a->size--;
        } else {
            // if the current node in Set a have a data that is already in
            // set b, move to the next node, so we are keeping it in set a
            prev = current;
            current = current->next;
        }
    }

    // Return a pointer to the difference Set
    return a;
}

int main() {

    printf("Initialize with duplicates\n");
    int v1[] = {1, 2, 2, 3};
    Set *set1 = (Set *)malloc(sizeof(Set));
    set_init(set1, v1, 4);
    set_print(set1); // Expected output: { 1 2 3 }
    printf("\n");


    printf("Initialize with negative numbers\n");
    int v2[] = {-1, -2, -3};
    Set *set2 = (Set *)malloc(sizeof(Set));
    set_init(set2, v2, 3);
    set_print(set2); // Expected output: { -1 -2 -3 }
    printf("\n");

    printf("Initialize an empty set\n");
    int v3[] = {};
    Set *set3 = (Set *)malloc(sizeof(Set));
    set_init(set3, v3, 0);
    set_print(set3); // Expected output: { }
    printf("\n");

    printf("Union of a set with itself\n");
    Set *union_self_set = set_union(set1, set1);
    set_print(union_self_set); // Expected output: { 1 2 3 }
    printf("\n");

    printf("Intersect of disjoint sets\n");
    int v4[] = {4, 5, 6};
    Set *set4 = (Set *)malloc(sizeof(Set));
    set_init(set4, v4, 3);
    Set *intersect_disjoint_set = set_intersect(set2, set4);
    set_print(intersect_disjoint_set); // Expected output: { }
    printf("\n");

    printf("Difference between a set and itself\n");
    Set *diff_self_set = set_diff(set1, set1);
    set_print(diff_self_set); // Expected output: { }
    printf("\n");

    printf("Difference where second set is a subset\n");
    set1 = (Set *)malloc(sizeof(Set));
    set_init(set1, v1, 4);
   int v5[] = {2, 3};
   Set *set5 = (Set *)malloc(sizeof(Set));
   set_init(set5, v5, 2);
   Set *diff_subset_set = set_diff(set1, set5);
   set_print(diff_subset_set); // Expected output: { 1 }
   printf("\n");

    printf("Print a set with one element\n");
   int v6[] = {1};
   Set *set6 = (Set *)malloc(sizeof(Set));
   set_init(set6, v6, 1);
   set_print(set6); // Expected output: { 1 }
    printf("\n");

    printf("Intersect with one set empty\n");
    Set *intersect_empty_set = set_intersect(set3, set1);
    set_print(intersect_empty_set); // Expected output: { }
     printf("\n");

    printf("Union with one set empty\n");
    Set *union_empty_set = set_union(set3, set1);
    set_print(union_empty_set); // Expected output: { 1 2 3 }
    printf("\n");

    printf("Difference with one set empty\n");
    Set *diff_empty_set = set_diff(set3, set1);
    set_print(diff_empty_set); // Expected output: { }
    printf("\n");

    printf("Test with sets having overlapping elements\n");
    int v7[] = {1, 2, 3, 4};
    Set *set7 = (Set *)malloc(sizeof(Set));
    set_init(set7, v7, 4);
    set_print(set7);
    int v8[] = {3, 4, 5, 6};
    Set *set8 = (Set *)malloc(sizeof(Set));
    set_init(set8, v8, 4);
    set_print(set8);
    printf("\n");

    printf("Union with overlapping elements\n");
    Set *union_overlap = set_union(set7, set8);
    set_print(union_overlap); // Expected output: { 1 2 3 4 5 6 }
    printf("\n");

    printf("Intersection with overlapping elements\n");
    Set *intersect_overlap = set_intersect(set7, set8);
    set_print(intersect_overlap); // Expected output: { 3 4 }
    printf("\n");

    printf("Difference with overlapping elements\n");
    set7 = (Set *)malloc(sizeof(Set));
    set_init(set7, v7, 4);
    Set *diff_overlap = set_diff(set7, set8);
    set_print(diff_overlap); // Expected output: { }
    printf("\n");

    printf("Test with sets having duplicate elements in the input array\n");
    int v9[] = {1, 2, 2, 3, 3, 3};
    Set *set9 = (Set *)malloc(sizeof(Set));
    set_init(set9, v9, 6);
    set_print(set9); // Expected output: { 1 2 3 }
    printf("\n");

    printf("Test the difference when the second set is empty\n");
    Set *diff_second_empty = set_diff(set7, set3);
    set_print(diff_second_empty); // Expected output: { }
    printf("\n");

    return 0;
}