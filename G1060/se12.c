#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

#define LINESIZE 128

typedef struct City City;
typedef struct GraphNode GraphNode;
typedef struct NeighbourNode NeighbourNode;
typedef struct StackNode StackNode;

struct City {
	int id;
	char* name;
};

struct GraphNode {
	City city;
	NeighbourNode* neighbour;
	GraphNode* next;
};

struct NeighbourNode {
	GraphNode* primaryNodeAddress;
	NeighbourNode* next;
};

struct StackNode {
	int id;
	StackNode* next;
};

void push(StackNode** head, int id) {
	StackNode* newNode = malloc(sizeof(StackNode));
	newNode->id = id;
	newNode->next = *head;
	*head = newNode;
}

int pop(StackNode** head) {
	int result = (*head)->id;
	StackNode* toDelete = *head;
	*head = (*head)->next;
	free(toDelete);
	return result;
}

void insertGraphNode(GraphNode** graph, City city) {
	GraphNode* newNode = malloc(sizeof(GraphNode));
	newNode->city = city;
	newNode->neighbour = NULL;
	newNode->next = NULL;
	if (*graph) {
		GraphNode* aux = *graph;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = newNode;
	}
	else {
		*graph = newNode;
	}
}

void printCity(City city) {
	printf("%d. %s\n", city.id, city.name);
}

void printNeighbours(NeighbourNode* start) {
	while (start) {
		printf("\t-> %d\n", start->primaryNodeAddress->city.id);
		start = start->next;
	}
	printf("--------------------\n");
}

void printGraph(GraphNode* graph) {
	while (graph) {
		printCity(graph->city);
		printNeighbours(graph->neighbour);
		graph = graph->next;
	}
}

GraphNode* searchNodeById(GraphNode* graph, int id) {
	while (graph && graph->city.id != id) {
		graph = graph->next;
	}
	return graph;
}

void insertNeighbour(NeighbourNode** start, GraphNode* primaryNode) {
	NeighbourNode* newNode = malloc(sizeof(NeighbourNode));
	newNode->primaryNodeAddress = primaryNode;
	newNode->next = NULL;

	if (*start) {
		NeighbourNode* aux = *start;
		while (aux->next) {
			aux = aux->next;
		}

		aux->next = newNode;
	}
	else {
		*start = newNode;
	}
}

void addEdge(GraphNode* graph, int startNodeId, int endNodeId) {
	GraphNode* startNode = searchNodeById(graph, startNodeId);
	GraphNode* endNode = searchNodeById(graph, endNodeId);

	if (startNode && endNode) {
		insertNeighbour(&(startNode->neighbour), endNode);
		insertNeighbour(&(endNode->neighbour), startNode);
	}
}

City readDataFromFile(FILE* f) {

	City city;

	char buffer[LINESIZE];
	fgets(buffer, LINESIZE, f);

	char* token = strtok(buffer, ",");
	city.id = atoi(token);

	token = strtok(NULL, ",");
	city.name = malloc((strlen(token) + 1) * sizeof(char));
	strcpy(city.name, token);

	return city;
}

void readAllFromFile(GraphNode** graph, const char* filename) {
	FILE* f;
	f = fopen(filename, "r");

	while (!feof(f)) {
		insertGraphNode(graph, readDataFromFile(f));
	}

	fclose(f);

	f = fopen("edges.txt", "r");
	while (!feof(f)) {

		char buffer[LINESIZE];
		fgets(buffer, LINESIZE, f);
		char* token = strtok(buffer, ",");
		int startId = atoi(token);
		token = strtok(NULL, ",");
		int stopId = atoi(token);
		addEdge(*graph, startId, stopId);
	}
	
	fclose(f);
}

void depthTraversal(GraphNode* graph, int startNodeId, int nodesNo) {

	StackNode* stack = NULL;
	int* visited = malloc(nodesNo * sizeof(int));

	for (int i = 0; i < nodesNo; i++) {
		visited[i] = 0;
	}

	visited[startNodeId - 1] = 1;
	push(&stack, startNodeId);

	while (stack) {
		int currentId = pop(&stack);
		GraphNode* currentNode = searchNodeById(graph, currentId);
		printCity(currentNode->city);
		NeighbourNode* neighbourList = currentNode->neighbour;

		while (neighbourList) {
			if (visited[neighbourList->primaryNodeAddress->city.id - 1] == 0) {
				visited[neighbourList->primaryNodeAddress->city.id - 1] = 1;
				push(&stack, neighbourList->primaryNodeAddress->city.id);
			}
			neighbourList = neighbourList->next;
		}
	}
}

int main() {
	GraphNode* graph = NULL;
	readAllFromFile(&graph, "cities.txt");
	printGraph(graph);
	depthTraversal(graph, 5, 7);
}

/*
1,A
2,B
3,C
4,D
5,E
6,F
7,G
*/

/*
1,4
1,3
1,6
2,4
2,5
2,7
3,4
3,6
5,7
6,7
*/
