#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// stack (lifo) struct
typedef struct Lifo {
	size_t capacity; // capacity of the stack
	size_t size; // current size of the stack
	int* arr; // array of elements
	int* curr; // pointer to the top of the stack
} Lifo;

// initialise a stack
int init_lifo(Lifo** stack) {

	// allocate memory for the stack

	*stack = malloc(sizeof(Lifo));

	// initialise fields

	(*stack)->capacity = 10;
	(*stack)->arr = malloc((*stack)->capacity * sizeof(int));
	(*stack)->size = 0;
	(*stack)->curr = (*stack)->arr;

	printf("Stack initialised:\n");
	printf("capacity = %zu\n", (*stack)->capacity);
	printf("size = %zu\n", (*stack)->size);
	printf("arr = %p\n", (*stack)->arr);
	printf("curr = %p\n", (*stack)->curr);

	return 0;
}


// move the top of the stack backward and put the top item in *dest
int pop_lifo(Lifo *stack, int *dest) {

	// if stack is empty, return -1 to notify about illegal operation

	if (stack->size == 0) {
		return -1;
	} else {

		// update stack fields

		--(stack->size);
		stack->curr -= 1;

		printf("reading %d from address %p\n", *(stack->curr), stack->curr);

		// put item into *dest

		*dest = *(stack->curr);
	}
	return 0;
}

// push element on the of a stack
int push_lifo(Lifo **stack, int value) {
	
	// if new_size > capacity, increase the capacity and reallocate
	
    if ((*stack)->size == (*stack)->capacity) {

        // create a new stack

        Lifo *new_stack = malloc(sizeof(Lifo));
        new_stack->capacity = (*stack)->capacity * 2;
        new_stack->arr = malloc(new_stack->capacity * sizeof(int));
        new_stack->size = (*stack)->size;

        // copy data into the new stack and free the old one
        
        printf("coyping stack from %p to %p\n", (*stack)->arr, new_stack->arr);
        memcpy(new_stack->arr, (*stack)->arr, (*stack)->size * sizeof(int));
        new_stack->curr = new_stack->arr + new_stack->size;
        free((*stack)->arr);
		free(*stack);
        *stack = new_stack;
    }

	// insert the element

	++((*stack)->size);
	printf("inserting %d at address %p (new size = %zu, capacity = %zu)\n", value, (*stack)->curr, (*stack)->size, (*stack)->capacity);

	// update stack fields

	*((*stack)->curr) = value;
	(*stack)->curr += 1;
	return 0;
}

int main() {
	srand(time(NULL));
	Lifo *q;
	init_lifo(&q);
	for (int i = 0; i < 100; ++i) {
		int r = rand() % 100;
		push_lifo(&q, r);
	}
	for (int i = 0; i < 100; ++i) {
		int v;
		int status = pop_lifo(q, &v);
		if (status == -1) {
			fprintf(stderr, "error while reading from the stack\n");
			return -1;
		}
		printf("read: %d\n", v);
	}
	printf("\n");
	free(q->arr);
	free(q);
}
