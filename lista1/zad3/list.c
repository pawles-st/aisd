#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// single element struct
struct Node {
	int value;
	struct Node *prev;
	struct Node *next;
};

typedef struct Node Node;

// list struct
typedef struct {
	Node *head;
} List;

// push an element to the front of a list
int push_front(List *list, int value) {

	if (list == NULL) {
		return -1;
	}

	// create a new node item

	Node *node = malloc(sizeof(Node));
	node->value = value;
	/*printf("inserting %d at address %p (head)\n", value, node);*/

	// insert the node into a list

	if (list->head != NULL) {
		node->next = list->head;
		node->prev = list->head->prev;
		list->head->prev->next = node;
		list->head->prev = node;
	} else {
		node->next = node;
		node->prev = node;
	}
	list->head = node;

	return 0;
}

// insert an element after a given one in a list
int insert_after(Node *prev, int value) {

	if (prev == NULL) {
		return -1;
	}

	// create a new node item

	Node *node = malloc(sizeof(Node));
	node->value = value;
	prev->next->prev = node;
	node->next = prev->next;
	node->prev = prev;
	/*printf("inserting %d at address %p\n", value, node);*/

	// insert the node into a list

	prev->next = node;

	return 0;
}

// remove the first element in a list
int pop_front(List *list) {

	if (list == NULL) {
		return -1;
	}

	list->head->next->prev = list->head->prev;
	list->head->prev->next = list->head->next;

	Node *new_head = list->head->next;
	//printf("removing %d from address %p (head)\n", list->head->value, list->head);
	free(list->head);
	list->head = new_head;

	return 0;
}

// remove an element after a given one in a list
int erase_after(Node *prev) {

	if (prev == NULL) {
		return -1;
	}

	Node *next = prev->next;
	prev->next = next->next;
	next->next->prev = prev;
	//printf("removing %d from address %p\n", next->value, next);
	free(next);

	return 0;
}

// move a pointer to the next element in a list
int next(Node **curr) {
	if (curr == NULL || *curr == NULL) {
		return -1;
	}

	//printf("progressing a pointer from %p to %p\n", *curr, (*curr)->next);
	*curr = (*curr)->next;

	return 0;
}

// move a pointer to the previous element in a list
int prev(Node **curr) {
	if (curr == NULL || *curr == NULL) {
		return -1;
	}

	*curr = (*curr)->prev;

	return 0;
}

// join two lists together; put result into the list of node
int merge(List *first, List *second) {

	// handle the case where node points to null

	if (second->head == NULL) {
		return 0;
	}

	if (first == NULL) {
		return -1;
	}

	if (first->head == NULL) {
		first->head = second->head;
	}

	Node *first_end = first->head->prev;
	Node *second_end = second->head->prev;

	// merge lists

	first_end->next = second->head;
	second->head->prev = first_end;
	first->head->prev = second_end;
	second_end->next = first->head;

	return 0;
}

int main() {
	srand(time(NULL));

	// basic operations test

	List l;
	l.head = NULL;
	push_front(&l, rand() % 100);
	Node *curr = l.head;
	/*printf("hnext: %p\n", l.head->next);*/

	for (int i = 0; i < 10000; ++i) {
		int r = rand() % 100;
		insert_after(curr, r);
		next(&curr);
	}
	/*printf("h: %p\n", l.head);*/

	for (int i = 0; i <= 10000; i += 1000) {
		clock_t start = clock();
		int v;
		for(int k = 0; k < 100; ++k) {
			curr = l.head;
			if (i <= 5000) {
				for (int j = 0; j < i; ++j) {
					next(&curr);
				}
			} else {
				for (int j = 0; j < 10001 - i; ++j) {
					prev(&curr);
				}
			}
			v = curr->value;
		}
		clock_t end = clock();
		printf("(%6d, %6d): %.8fs\n", i, v, ((double) (end - start)) / CLOCKS_PER_SEC / 100);
	}

	int idx[100];
	for (int k = 0; k < 100; ++k) {
		idx[k] = rand() % 10000;
	}
	clock_t start = clock();
	for (int k = 0; k < 100; ++k) {
		curr = l.head;
		if (idx[k] <= 5000) {
			for (int j = 0; j < idx[k]; ++j) {
				next(&curr);
			}
		} else {
			for (int j = 0; j < 10001 - idx[k]; ++j) {
				prev(&curr);
			}
		}
		int v = curr->value;
	}
	clock_t end = clock();
	printf("random: %.8fs\n", ((double) end - start) / CLOCKS_PER_SEC / 100);

	// merge test
	
	List l1, l2;
	l1.head = NULL;
	l2.head = NULL;
	push_front(&l1, rand() % 100);
	push_front(&l2, rand() % 100);

	curr = l1.head;
	for (int i = 0; i < 5; ++i) {
		int r = rand() % 20;
		insert_after(curr, r);
		next(&curr);
	}

	curr = l2.head;
	for (int i = 0; i < 5; ++i) {
		int r = rand() % 20;
		insert_after(curr, r);
		next(&curr);
	}

	curr = l1.head;
	do {
		printf("%d, ", curr->value);
		curr = curr->next;
	} while (curr != l1.head);
	printf("\n");
	curr = l2.head;
	do {
		printf("%d, ", curr->value);
		curr = curr->next;
	} while (curr != l2.head);
	printf("\n");

	start = clock();
	merge(&l1, &l2);
	end = clock();
	printf("merge: %.8fs\n", ((double) end - start) / CLOCKS_PER_SEC);

	curr = l1.head;
	do {
		printf("%d, ", curr->value);
		curr = curr->next;
	} while (curr != l1.head);
	printf("\n");

	// deletion

	curr = l.head;
	for (int i = 0; i < 10000; ++i) {
		pop_front(&l);
	}
	curr = l2.head;
	for (int i = 0; i < 5; ++i) {
		pop_front(&l2);
	}
}
