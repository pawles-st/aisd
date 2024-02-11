#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// queue (fifo) struct
typedef struct Fifo {
	size_t capacity; // capacity of the queue
	size_t size; // current size of the queue
	int* arr; // array of elements
	int* head; // pointer to the head of the queue
	int* tail; // pointer to the tail of the queue
} Fifo;


// initialise a queue
int init_fifo(Fifo** queue) {

	// allocate memory for the queue

	*queue = malloc(sizeof(Fifo));

	// initialise fields

	(*queue)->capacity = 10;
	(*queue)->arr = malloc((*queue)->capacity * sizeof(int));
	(*queue)->size = 0;
	(*queue)->head = (*queue)->arr;
	(*queue)->tail = (*queue)->arr;

	printf("Queue initialised:\n");
	printf("capacity = %zu\n", (*queue)->capacity);
	printf("size = %zu\n", (*queue)->size);
	printf("arr = %p\n", (*queue)->arr);
	printf("head = %p\n", (*queue)->head);
	printf("tail = %p\n", (*queue)->tail);

	return 0;
}

// move the head of the queue forward and put the first item in *dest
int pop_fifo(Fifo *queue, int *dest) {

	// if queue is empty, return -1 to notify about illegal operation

	if (queue->size == 0) {
		return -1;
	} else {
		
		// put item into *dest
		
		printf("reading %d from address %p\n", *(queue->head), queue->head);

		*dest = *(queue->head);

		// update queue fields

		--(queue->size);
		queue->head += 1;

		// loop back the pointer if needed

		if (queue->head == queue->arr + queue->capacity) {
			queue->head = queue->arr;
		}
	}
	return 0;
}

// push element on the tail of the queue
int push_fifo(Fifo **queue, int value) {
	
	// if new_size > capacity, increase the capacity and reallocate
	
    if (((*queue)->size) == (*queue)->capacity) {

		// create a new queue

		Fifo *new_queue = malloc(sizeof(Fifo));
		new_queue->capacity = (*queue)->capacity * 2;
		new_queue->arr = malloc(new_queue->capacity * sizeof(int));
		new_queue->size = (*queue)->size;
		new_queue->head = new_queue->arr;

		// copy data into the new queue and free the old one
		
		printf("coyping queue from %p to %p\n", (*queue)->arr, new_queue->arr);

		if ((*queue)->tail >= (*queue)->head) {
			memcpy(new_queue->head, (*queue)->head, (*queue)->size * sizeof(int));
		} else {
			int half_size = (*queue)->arr + (*queue)->capacity - (*queue)->head;
			memcpy(new_queue->head, (*queue)->head, half_size * sizeof(int));
			memcpy(new_queue->head + half_size, (*queue)->tail, ((*queue)->size - half_size) * sizeof(int));
		}
		new_queue->tail = new_queue->arr + new_queue->size;
		free((*queue)->arr);
		free(*queue);
		*queue = new_queue;
	}

	// insert the element

	++((*queue)->size);
	printf("inserting %d at address %p (new size = %zu, capacity = %zu)\n", value, (*queue)->tail, (*queue)->size, (*queue)->capacity);

	// update queue fields

	*((*queue)->tail) = value;
	(*queue)->tail += 1;

	// loop back the pointer if needed
	
	if ((*queue)->tail == (*queue)->arr + (*queue)->capacity) {
		(*queue)-> tail = (*queue)->arr;
	}

	return 0;
}

int main() {
	srand(time(NULL));
	Fifo *q;
	init_fifo(&q);
	for (int i = 0; i < 100; ++i) {
		int r = rand() % 100;
		push_fifo(&q, r);
	}
	for (int i = 0; i < 100; ++i) {
		int v;
		int status = pop_fifo(q, &v);
		if (status == -1) {
			fprintf(stderr, "error while reading from the queue\n");
			return -1;
		}
		printf("read: %d\n", v);
	}
	printf("\n");
	free(q->arr);
	free(q);
}
