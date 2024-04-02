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

//TODO: check if there is enough memory FOR ALL FUNCTIONS!!!

/* Gets the address of an array of integers, and the size of the array,
   and returns the address of the first element in the copy of the array,
   using dynamic allocation */
int *copyarray(int *elements, int size) {
    // Check if the input is invalid
    if (elements == NULL || size < 0) {
        printf("Invalid input\n");
        return 0;
    }

    // Dynamically allocate memory for the new array
    int *elements_copy = (int *)malloc(size * sizeof(int));

    // Check if memory allocation was successful
    if (elements_copy == NULL) {
        printf("Out of Memory\n");
        return 0;
    } else // Memory allocation was successful{
        printf("Memory allocated successfully\n");
    int i = 0;
    // Copy the elements of the array to the new array
    while (i < size) {
        elements_copy[i] = elements[i];
        i++;
    }

    // Return the address of the first element in the copy of the array
    return elements_copy;
}

/* Gets the address of an array of integers, and the size of the array,
   and returns the address of the first element in the sorted array,
   using dynamic allocation */
int *sort_arr(int *elements, int size) {
    // Copy the array, using the copyarray method, that using dynamic allocation
    int *elements_copy = copyarray(elements, size);

    // Sort the array in ascending order,
    // using the insertion sort algorithm
    for (int j = 1; j < size; j++) {
        // Insert elements[j] into the sorted sequence elements,
        // till the element, elements[j-1],
        int value = elements_copy[j];
        int i = j - 1;
        // Find the correct position for elements[j] in the sorted sequence
        while ((i >= 0) && (elements_copy[i] > value)) {
            // Shift elements[i] to the right
            int *p_temp = (elements_copy + (i + 1));
            // Insert elements[j] into the correct position
            *p_temp = *(elements_copy + i);
            --i;
        }
        // Insert elements[j] into the correct position
        int *p_temp = (elements_copy + (i + 1));
        // Insert elements[j] into the correct position
        *p_temp = value;
    }

    // Remove duplicates
    int new_size = 0;
    // Loop through the sorted coins array
    for (int i = 0; i < size; i++) {
        // Check if the current element is not a duplicate
        if ((i == 0) || (elements[i] != elements[i - 1])) {
            // if unique element, copy it to the correct position
            elements[new_size] = elements[i];
            new_size++;
        }
    }

    //add the new size to array as the first element, and shift all of the
    //elements in the array one place right
    elements = (int *)malloc((new_size + 1) * sizeof(int));
    elements[0] = new_size;
    for (int i = 1; i < new_size + 1; i++) {
        elements[i] = elements_copy[i - 1];
    }

    // Return the address of the first element in the sorted array
    return elements;
}

int *array_union(int *a_array, int a_size, int *b_array, int b_size) {
    int *c_array = (int *)malloc((a_size + b_size) * sizeof(int));
    int i = 0;
    while (i < a_size) {
        c_array[i] = a_array[i];
        i++;
    }
    for (int j = 0; j < b_size; j++) {
        c_array[i] = b_array[j];
        i++;
    }
    c_array = sort_arr(c_array, a_size);
    return c_array;
}

/* This function is a helping function that used to insert a node at the end of
 * the linked-list. */
void insert_at_end(int data, node_t *head) {
    // create a link
    node_t *lk = (node_t*) malloc(sizeof(node_t));
    lk->data = data;
    lk->next = NULL; // Make sure the new node points to NULL as it is the last node
    node_t *linked_list = head;
    // Traverse to the last node
    while (linked_list->next != NULL) {
        linked_list = linked_list->next;
    }
    // Append the new node to the end of the list
    linked_list->next = lk;
}

/* This function is used for the creation of set s, using memory allocation,
 * and placement the members of the set of the given array. */
void set_init(Set *s, int v[], int num_elements_in_v) {
    // Dynamically allocate memory for the head node
    s->head = (node_t*) malloc(sizeof(node_t));
    s->head->next = NULL; // Initialize the next pointer of the head node to NULL
    for (int i = 0; i < num_elements_in_v; i++) {
        insert_at_end(v[i], s->head);
        s->size++;
    }
}

/* This function is used for print the members of the set s, according to the
 * order of the nodes in the linked-list.
 * Also, used any time we are creating a new set. */
void set_print(Set *s) {
    printf("{ ");
    node_t *linked_list = s->head->next; // Skip the head node
    while (linked_list != NULL) {
        printf("%d ", linked_list->data);
        linked_list = linked_list->next;
    }
    printf("}\n");
}

/* This function gets the address of two instances of sets,
 * prints each one of them,
 * and returns a new set(using "set_init") of the union of them. */
Set* set_union(Set *a, Set *b) { //TODO: debug
    // prints set a
    set_print(a);
    // prints set b
    set_print(b);


    node_t *a_linked_list = a->head;
    int *a_array = (int *)malloc((a->size) * sizeof(int));
    int i = 0;
    while (a_linked_list->next != NULL) {
        a_array[i] = a_linked_list->data;
        a_linked_list = a_linked_list->next;
        i++;
    }

    node_t *b_linked_list = b->head;
    int *b_array = (int *)malloc((b->size) * sizeof(int));
    i = 0;
    while (b_linked_list->next != NULL) {
        b_array[i] = b_linked_list->data;
        b_linked_list = b_linked_list->next;
        i++;
    }

    // creates pointer to the pointer of the union
    Set *union_set = (Set *) malloc(sizeof(Set));

    int *union_array_1 = (int *)malloc((a->size + b->size) * sizeof(int));
    union_array_1 = array_union(a_array, a->size, b_array, b->size);

    int union_size = union_array_1[0];
    int *union_array_2 = (int *)malloc((union_size) * sizeof(int));
    i = 0;
    for (int j = 1; j < union_size; j++) {
        union_array_2[i] = union_array_1[j];
        i++;
    }

    set_init(union_set, union_array_2, union_size);

    set_print(union_set);

    return union_set;
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



int main() {
    int a_size = 4;
    int a_arr[4] = {1, 3, 2, 1};
    Set *a = (Set *) malloc(sizeof(Set));
    set_init(a, a_arr, a_size);
    int b_size = 3;
    int b_arr[3] = {5, 3, 6};
    Set *b = (Set *) malloc(sizeof(Set));
    set_init(b, b_arr, b_size);
    set_union(a, b);
    return 0;
}
