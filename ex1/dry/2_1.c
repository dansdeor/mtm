#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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

Node mergeSortedLists(Node list1, Node list2, ErrorCode* error_code);


bool isListSorted(Node list)
{
	if (list == NULL) {
		return true;
	}
	Node first = list;
	Node second = list->next;
	while (first != NULL && second != NULL) {
		if (first->x > second->x) {
			return false;
		}
		first = second;
		second = second->next;
	}
	return true;
}


static Node copyNode(Node node)
{
	if (node == NULL) {
		return NULL;
	}
	Node new_node = malloc(sizeof(*new_node));
	if (new_node == NULL) {
		return NULL;
	}
	new_node->x = node->x;
	new_node->next = NULL;
	return new_node;
}


static bool appendList(Node dest, Node src)
{
	if (dest == NULL) {
		return false;
	}
	while (dest->next != NULL) {
		dest = dest->next;
	}
	while (src != NULL) {
		Node new_node = copyNode(src);
		if (new_node == NULL) {
			return false;
		}
		dest->next = new_node;
		dest = dest->next;
		src = src->next;
	}
	return true;
}


static void destroyList(Node list)
{
	Node iterator = list;
	while (list != NULL) {
		iterator = iterator->next;
		free(list);
		list = iterator;
	}
}


Node mergeSortedLists(Node list1, Node list2, ErrorCode* error_code)
{
	if (list1 == NULL || list2 == NULL || error_code == NULL) {
		if (error_code != NULL) {
			*error_code = NULL_ARGUMENT;
		}
		return NULL;
	}
	if (!isListSorted(list1) || !isListSorted(list2)) {
		*error_code = UNSORTED_LIST;
		return NULL;
	}
	Node head, iterator = NULL;
	while (list1 != NULL && list2 != NULL) {
		Node new_node;
		if (list1->x <= list2->x) {
			new_node = copyNode(list1);
			list1 = list1->next;
		}
		else {
			new_node = copyNode(list2);
			list2 = list2->next;
		}
		if (new_node == NULL) {
			destroyList(head);
			*error_code = MEMORY_ERROR;
			return NULL;
		}
		if (iterator == NULL) {
			head = new_node;
			iterator = new_node;
		}
		else {
			iterator->next = new_node;
			iterator = new_node;
		}
	}
	Node added_node = (list1 != NULL) ? list1 : list2;
	if (!appendList(iterator, added_node)) {
		destroyList(head);
		*error_code = MEMORY_ERROR;
		return NULL;
	}
	*error_code = SUCCESS;
	return head;
}


int main()
{
	struct node_t node1_3 = {8, NULL};
	struct node_t node1_2 = {4, &node1_3};
	struct node_t node1_1 = {2, &node1_2};

	struct node_t node2_4 = {10, NULL};
	struct node_t node2_3 = {9, &node2_4};
	struct node_t node2_2 = {4, &node2_3};
	struct node_t node2_1 = {1, &node2_2};

	ErrorCode error_code;
	Node head = mergeSortedLists(&node1_1, &node2_1, &error_code);
	printf("ErrorCode: %d\n", error_code);
	Node iterator = head;
	while (iterator != NULL) {
		printf("%d\n", iterator->x);
		iterator = iterator->next;
	}
	destroyList(head);
	return 0;
}
