#include <stdio.h>
#include <stdlib.h>

typedef char * string;

typedef struct node {
	int data;
	struct node *next;
	struct node *prev;
} Node;

typedef struct list {
	Node *head;
	Node *tail;
	int   size;
} List;

List *create_list() {
	List *list = (List *)malloc(sizeof(List));
	if(list == NULL) {
		perror("Memory allocation failed.");
		exit(1);
	}
	list->head = NULL;
	list->tail = NULL;
	
	return list;
}

void add_node(List *list, int data) {
	Node *n = (Node *)malloc(sizeof(Node));
	if(n == NULL) {
		perror("Memory allocation failed.");
		exit(1);
	}
	n->data = data;
	n->next = NULL;
	if(list->head == NULL) {
		list->head = n;
		list->tail = n;
	} else {
		list->tail->next = n;
		list->tail = list->tail->next;
	}
}

void print_list(List *list) {
	Node *t = list->head;
	while(t != NULL) {
		printf("%d ", t->data);
		t = t->next;
	}
}

void destroy_list(List *list) {
	Node *t;
	if(list != NULL) {
		while(list->head != NULL) {
			t = list->head->next;
			free(list->head);
			list->head = t;
		}
		free(list);
	}
}

int main(void) {
	List *inventory = create_list();
	
	int i;
	for(i = 0; i < 10; i++) {
		add_node(inventory, i);
	}
	
	print_list(inventory);
	
	destroy_list(inventory);
	return 0;
}