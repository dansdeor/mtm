#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <mmcobj.h>

typedef struct node_t {
    int x;
    struct node_t *next;
} *Node;

node_t* sortedMerge(node_t *a, node_t *b);

typedef enum {
    SUCCESS=0,
    MEMORY_ERROR,
    UNSORTED_LIST,
    NULL_ARGUMENT,
} ErrorCode;

int getListLength(Node list);
bool isListSorted(Node list);


Node mergeSortedLists(Node list1, Node list2, ErrorCode* error_code){
    node_t *a= list1;
    node_t *b= list2;
    sortedMerge(&a,&b);
}


node_t* sortedMerge(node_t *a, node_t *b) {
    node_t dummy, *tail = &dummy;
    dummy.next = NULL;
    while (a != NULL && b != NULL) {
        if (a->x <= b->x) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    if (a == NULL) {
        tail->next = b;
    } else { // b == NULL
        tail->next = a;
    }
    return dummy.next;
}
