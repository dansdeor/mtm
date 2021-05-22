#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct node_t {
    int x;
    struct node_t* next;
} * Node;


typedef enum {
    SUCCESS = 0,
    MEMORY_ERROR,
    UNSORTED_LIST,
    NULL_ARGUMENT,
} ErrorCode;

int getListLength(Node list);

bool isListSorted(Node list);


Node mergeSortedLists(Node list1, Node list2, ErrorCode* error_code)
{
    if (list1 == NULL || list2 == NULL || error_code == NULL) {
        if (error_code == NULL) {
            *error_code = NULL_ARGUMENT;
        }
        return NULL;
    }
    if (!isListSorted(list1) || !isListSorted(list2)) {
        *error_code = UNSORTED_LIST;
        return NULL;
    }
    Node head = NULL;
    Node iterator = NULL;
    while (list1 != NULL || list2 != NULL) {
        Node added_node;
        if (list1->x <= list2->x) {
            added_node = list1;
            list1 = list1->next;
        } else {
            added_node = list2;
            list2 = list2->next;
        }
        Node new_node = malloc(sizeof(*new_node));
        if (new_node == NULL) {
            *error_code = MEMORY_ERROR;
            return NULL;
        }
        new_node->x = added_node->x;
        new_node->next = NULL;
        if (head == NULL && iterator == NULL) {
            head = new_node;
            iterator = new_node;
        } else {
            iterator->next = new_node;
            iterator = new_node;
        }
    }
    if (list1 == NULL) {
        iterator->next = list2;
    } else {
        iterator->next=list1;
    }
    *error_code = SUCCESS;
    return head;
}


