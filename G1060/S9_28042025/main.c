#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define LINESIZE 128

typedef struct Task Task;
typedef struct Heap Heap;

struct Task {
	char* description;
	int priority;
};

struct Heap {
	Task* tasks;
	int size;
};

void swapTask(Task* t1, Task* t2) {
	Task aux = *t1;
	*t1 = *t2;
	*t2 = aux;
}

Task initTask(char* description, int priority) {
	Task task = { .priority = priority };
	task.description = malloc((strlen(description) + 1) * sizeof(char));
	strcpy(task.description, description);
	return task;
}

void printTaskToConsole(Task task) {
	printf("%s - priority %d\n", task.description, task.priority);
}

Heap initHeap() {
	Heap heap;
	heap.size = 0;
	heap.tasks = malloc(heap.size * sizeof(Task));
	return heap;
}

void insertHeap(Heap* heap, Task task) {

	heap->size += 1;
	heap->tasks = realloc(heap->tasks, heap->size * sizeof(Task));

	int element_index = heap->size - 1;

	heap->tasks[element_index] = task;

	int parent_index = (element_index - 1) / 2;

	while (heap->tasks[element_index].priority > heap->tasks[parent_index].priority) { // max-heap condition not met

		swapTask(&heap->tasks[element_index], &heap->tasks[parent_index]);

		element_index = parent_index;
		
		parent_index = (element_index - 1) / 2;

	}

}

void printHeap(Heap heap) {
	for (int i = 0; i < heap.size; i++) {
		printf("%d ", heap.tasks[i].priority);
	}
	printf("\n");
}

void heapify(Heap heap, int index) {

	int largest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < heap.size && heap.tasks[left].priority > heap.tasks[largest].priority) {
		largest = left;
	}

	if (right < heap.size && heap.tasks[right].priority > heap.tasks[largest].priority) {
		largest = right;
	}

	if (largest != index) {

		swapTask(&heap.tasks[largest], &heap.tasks[index]);

		heapify(heap, largest);
	}

}

Heap buildHeap(Task* tasks, int size) {
	Heap heap;
	heap.size = size;
	heap.tasks = malloc(size * sizeof(Task));

	
	for (int i = 0; i < size; i++) {
		heap.tasks[i] = initTask(tasks[i].description, tasks[i].priority);
	}

	int startIndex = heap.size / 2 - 1;

	for (int i = startIndex; i >= 0; i--) {
		heapify(heap, i);
	}

	return heap;
}

Task deleteFromHeap(Heap* heap) {

	Task task = heap->tasks[0];

	swapTask(&heap->tasks[0], &heap->tasks[heap->size - 1]);
	
	heap->size -= 1;

	heap->tasks = realloc(heap->tasks, heap->size * sizeof(Task));

	int startIndex = heap->size / 2 - 1;

	for (int i = startIndex; i >= 0; i--) {
		heapify(*heap, i);
	}

	return task;
}

Task readTaskFromFile(FILE* f) {

	Task task;

	char buffer[LINESIZE];

	fgets(buffer, LINESIZE, f);
	char* token = strtok(buffer, ",");
	task.priority = atoi(token);
	
	token = strtok(NULL, ",");
	task.description = malloc((strlen(token) + 1) * sizeof(char));
	strcpy(task.description, buffer);

	return task;
}

void readTasksFromFile(const char* filename, Heap** heap) {

	FILE* f;
	f = fopen(filename, "r");

	while (!feof(f)) {
		insertHeap(heap, readTaskFromFile(f));

	}

	fclose(f);
}

int main() {

	printf("\n-------------\n");
	
	Heap heap = initHeap();
	readTasksFromFile("scheduler.txt", &heap);

	printHeap(heap);


	insertHeap(&heap, initTask("Task Z", 27));

	printHeap(heap);

	printf("\n-------------\n");


	Task tasks[7];
	for (int i = 0; i < 7; i++) {
		Task t = {.priority = i, .description = "Task X"};
		tasks[i] = t;
	}
	printf("\n");
	
	Heap heap2 = buildHeap(tasks, 7);

	printHeap(heap2);

	Task deletedTask = deleteFromHeap(&heap2);
	printTaskToConsole(deletedTask);
	free(deletedTask.description);
	printHeap(heap2);

	return 0;
	
}

/*
Scheduler.txt
4,Task A
10,Task B
9,Task C
19,Task D
1,Task E
29,Task F
14,Task G
7,Task H
*/