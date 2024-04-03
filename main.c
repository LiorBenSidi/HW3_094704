#include <stdio.h>
#include "stdlib.h"

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} node_t; // struct that represents a bidirectional node, for using at Traverse linked list

typedef struct {
    node_t *head;
    int size;
} Set; // struct that represents a set in math

/* This function is a helping function that used to insert a node at the end of
 * the linked-list. similar implementation to the function we have already
 * seen at the tutorial
 * */
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
    } else if (s->size == 0) { // check if the given Set is empty
        printf("{ }\n");
        return;
    }

    // Dynamically allocate memory for the new head "attribute" in Set s
    s->head = (node_t*) malloc(sizeof(node_t));

    // Check if memory allocation was successful
    if (s->head == NULL) {
        printf("Error: Out of Memory\n");
        return;
    } else { // Memory allocation was successful
        printf("Memory allocated successfully\n");
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
        printf("Error: The 'head' attribute is point to NULL");
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
            printf("%d ", current->data);
        }

        // gets the next node
        current = current->next;
    }

    printf("}\n");
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
//TODO: לשנות "סגנון" כתיבה של הקוד
Set* set_union(Set *a, Set *b) {
    // Input validation
    if (a == NULL || b == NULL) {
        return NULL; // Cannot perform union on NULL sets
    }

    //prints set a
    set_print(a);
    //prints set b
    set_print(b);

    // Allocate memory for the temporary array, handle empty sets by initializing count to 0
    int count = 0;
    int *temp = (int *)malloc(sizeof(int) * (a->size + b->size));
    if (temp == NULL) {
        return NULL; // Memory allocation failed
    }

    // Process set a, skip if set is empty
    node_t *current = a->head ? a->head->next : NULL;
    while (current) {
        temp[count++] = current->data;
        current = current->next;
    }

    // Process set b, adding only unique elements
    current = b->head ? b->head->next : NULL;
    while (current) {
        if (!is_element_in_array(current->data, temp, count)) {
            // Check for allocation failure inside the loop for each new element
            if (count >= (a->size + b->size)) {
                // Resize temp array if more space is needed
                int *new_temp = (int *)realloc(temp, sizeof(int) * (count + 1));
                if (new_temp == NULL) {
                    free(temp); // Free temp before returning to avoid memory leak
                    return NULL; // Memory allocation failed
                }
                temp = new_temp;
            }
            temp[count++] = current->data;
        }
        current = current->next;
    }

    // Initialize the new set with the unique elements
    Set *union_set = (Set *)malloc(sizeof(Set));
    if (union_set == NULL) {
        free(temp); // Clean up temp array before returning
        return NULL; // Memory allocation failed
    }
    set_init(union_set, temp, count);
    free(temp); // No longer needed, free the temporary array

    return union_set;
}

/* This function gets the address of two instances of sets,
 * prints each one of them,
 * and returns the intersect of them,
 * while the returned set must be one of the given sets(in place). */
//TODO: לשנות "סגנון" כתיבה של הקוד
Set* set_intersect(Set *a, Set *b) {
    // Validate input sets
    if (a == NULL || b == NULL) {
        return NULL;
    }

    //prints set a
    set_print(a);
    //prints set b
    set_print(b);

    // Decide which set to modify; here we choose the first set 'a'
    Set *result_set = a;
    node_t *current = result_set->head->next; // Start with the first actual data node
    node_t *prev = result_set->head;

    while (current != NULL) {
        // If the current element is not in set 'b', remove it from 'a'
        if (!is_exist_already(b, current->data)) {
            prev->next = current->next;
            if (current->next != NULL) {
                current->next->prev = prev;
            }
            free(current); // Free the memory of the removed node
            current = prev->next; // Move to the next node
            result_set->size--; // Decrement the size of the set
        } else {
            prev = current;
            current = current->next; // Move to the next node
        }
    }

    // Since we've modified the set 'a', it now contains the intersection
    return result_set;
}

/* This function gets the address of two instances of sets,
 * prints each one of them,
 * and returns the intersect of them,
 * while the returned set can be one of the given sets(in place),
 * or a new set. */
//TODO: לשנות "סגנון" כתיבה של הקוד
Set* set_diff(Set *a, Set *b) {
    // Validate input sets
    if (a == NULL || b == NULL) {
        printf("One or both sets are NULL.\n");
        return NULL;
    }

    // Print set a
    set_print(a);
    // Print set b
    set_print(b);

    // Iterate over set a and remove elements that are also in set b
    node_t *current = a->head->next; // Start from the first actual data node
    node_t *prev = a->head;

    while (current != NULL) {
        // Check if the current element is in set b
        if (is_exist_already(b, current->data )) {
            // Remove the current element from set a
            prev->next = current->next;
            if (current->next != NULL) {
                current->next->prev = prev;
            }
            free(current); // Free the node
            current = prev->next; // Move to the next node
            a->size--; // Decrement the size of set a
        } else {
            prev = current;
            current = current->next; // Move to the next node
        }
    }

    // The modified set a now contains the set difference
    return a;
}

int main() {
    // Edge Case: Initialize with duplicates
    int v1[] = {1, 2, 2, 3};
    Set *set1 = (Set *)malloc(sizeof(Set));
    set_init(set1, v1, 4);
    set_print(set1); // Expected output: { 1 2 3 }

    // Edge Case: Initialize with negative numbers
    int v2[] = {-1, -2, -3};
    Set *set2 = (Set *)malloc(sizeof(Set));
    set_init(set2, v2, 3);
    set_print(set2); // Expected output: { -1 -2 -3 }

    // Edge Case: Initialize an empty set
    int v3[] = {};
    Set *set3 = (Set *)malloc(sizeof(Set));
    set_init(set3, v3, 0);
    set_print(set3); // Expected output: { }

    // Edge Case: Union of a set with itself
    Set *union_self_set = set_union(set1, set1);
    set_print(union_self_set); // Expected output: { 1 2 3 }

    // Edge Case: Intersect of disjoint sets
    int v4[] = {4, 5, 6};
    Set *set4 = (Set *)malloc(sizeof(Set));
    set_init(set4, v4, 3);
    Set *intersect_disjoint_set = set_intersect(set2, set4);
    set_print(intersect_disjoint_set); // Expected output: { }

    // Edge Case: Difference between a set and itself
    Set *diff_self_set = set_diff(set1, set1);
    set_print(diff_self_set); // Expected output: { }

    // Edge Case: Difference where second set is a subset
    //TODO: why not working properly
    int v5[] = {2, 3};
    Set *set5 = (Set *)malloc(sizeof(Set));
    set_init(set5, v5, 2);
    Set *diff_subset_set = set_diff(set1, set5);
    set_print(diff_subset_set); // Expected output: { 1 }

    // Edge Case: Print a set with one element
    //TODO: why not working properly
    int v6[] = {1};
    Set *set6 = (Set *)malloc(sizeof(Set));
    set_init(set6, v6, 1);
    set_print(set6); // Expected output: { 1 }

    // Edge Case: Intersect with one set empty
    Set *intersect_empty_set = set_intersect(set3, set1);
    set_print(intersect_empty_set); // Expected output: { }

    // Edge Case: Union with one set empty
    //TODO: why not working properly
    Set *union_empty_set = set_union(set3, set1);
    set_print(union_empty_set); // Expected output: { 1 2 3 }

    // Edge Case: Difference with one set empty
    Set *diff_empty_set = set_diff(set3, set1);
    set_print(diff_empty_set); // Expected output: { }

    // TODO: Add memory deallocation for all initialized sets

    return 0;
}
