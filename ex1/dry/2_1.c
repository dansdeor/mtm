#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <mmcobj.h>

typedef struct node_t {
    int num;
    struct node_t *next;
} *Node;

Node* sortedMerge(node_t *list1, node_t *list2);

typedef enum {
    SUCCESS=0,
    MEMORY_ERROR,
    UNSORTED_LIST,
    NULL_ARGUMENT,
} ErrorCode;

int getListLength(Node list);
bool isListSorted(Node list);


Node mergeSortedLists(struct node_t* list1, Node list2, ErrorCode* error_code){
   ;
    sortedMerge(list1,list2);
    error_code= SUCCESS;
   /* return SUCCESS;
    return MEMORY_ERROR;
    return NULL_ARGUMENT;
    return */
    return error_code;
}


Node * sortedMerge(node_t *list1, node_t *list2) {
    node_t dummy, *tail = &dummy;
    dummy.next = NULL;
    while (list1 != NULL && list2 != NULL) {
        if (list1->num <= list2->num) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    if (list1 == NULL) {
        tail->next = list2;
    } else { // list2 == NULL
        tail->next = list1;
    }
    return dummy.next;
}
