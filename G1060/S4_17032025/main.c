#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

typedef struct Car Car;
typedef struct Node Node;

struct Car {
	int year;
	char* manufacturer;
	float cc;
};

struct Node {
	Car car;
	Node* next;
};

void insertAtBeginning(Node** start, Car car) {
	
	Node* newNode = malloc(sizeof(Node));

	newNode->car = car;
	newNode->next = *start;

	*start = newNode;
}

void insertAtEnd(Node** start, Car car) {

	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;
	newNode->next = NULL;

	if (*start) {

		Node* aux = *start;

		while (aux->next) {
			aux = aux->next;
		}

		aux->next = newNode;

	}
	else {
		*start = newNode;		
	}
}

Car deleteFromBeginning(Node** start) {

	// Check if list is not empty
	if (*start) {
		Node* deleted = *start;
		*start = (*start)->next;
	
		Car deletedCar = deleted->car;
		free(deleted);
	
		return deletedCar;
	} else {
		printf("List is empty\n");
		Car err = {.year = 0, .manufacturer = "ERR", .cc = 0};
		return err;
	}
	
}

Car deleteFromEnd(Node** start) {
	if (*start) {
		if ((*start)->next) {

			Node* aux = *start;
			while (aux->next->next) {
				aux = aux->next;
			}

			Node* deletedNode = aux->next;

			Car deletedCar = deletedNode->car;
			aux->next = NULL;
			free(deletedNode);

			return deletedCar;


		} else {
			Node* deleted = *start;
			*start = NULL;

			Car deletedCar = deleted->car;
			free(deleted);

			return deletedCar;
		}
	} else {
		printf("List is empty\n");
		Car err = {.year = 0, .manufacturer = "ERR", .cc = 0};
		return err;
	}
}

// Match condition and delete
void deleteCarByManufacturer(Node** start, const char* manufacturer) {
	// Check list to not be empty
	if (*start) {

		// Since we don't know what we'll delete, we keep track of current and previous node 
		Node* previous = NULL;
		Node* current = *start;

		// Loop to parse the list
		while (current) {
			// We hit a match
			if (strcmp(current->car.manufacturer,manufacturer) == 0) {
				// If we have previous it means that we passed by the first node
				if (previous) {

					Node* toBeDeleted = current;
					// We positioned ourselves on the node that we want to delete
					// We make the link from the previous node to the next node
					//  [] ->    [] ->     []
					// prev   current     next
					// we also update the current node to point to the next
					previous->next = current->next;
					current = current->next;

					// Delete the node
					free(toBeDeleted->car.manufacturer);
					free(toBeDeleted);

				// IF we don't have a previous it means that we are on the first node of the list
				} else {

					Node* toBeDeleted = current;

					// Move the current to the next one
					current = current->next;
					// Update the start of the list
					*start = current;

					// delete the node;
					free(toBeDeleted->car.manufacturer);
					free(toBeDeleted);
					// !!! Notice how we don't update the previous because it remains NULL, since we are still on the first node of the list
				}
			// We didn't hit a match, we move on, updating previous and current
			} else {
				previous = current;
				current = current->next;
			}
		}
		
	} else {
		printf("List is empty");
	}
}


void printCar(Car car) {
	printf("%s from %d has %5.2f\n", car.manufacturer, car.year, car.cc);
}

void parseListAndPrint(Node* start) {
	while (start) {
		printCar(start->car);
		start = start->next;
	}
}

Car readCarFromFile(FILE* f) {

	char buffer[LINESIZE];

	fgets(buffer, LINESIZE, f);

	Car car;

	char* carData = NULL;

	carData = strtok(buffer, ",");
	car.year = atoi(carData);

	carData = strtok(NULL, ",");
	car.manufacturer = malloc((strlen(carData) + 1) * sizeof(char));
	strcpy(car.manufacturer, carData);

	carData = strtok(NULL, ",");
	car.cc = atof(carData);

	return car;

}

void readCarsFromFile(Node** start, int* noCars, const char* fileName) {

	FILE* f;
	f = fopen(fileName, "r");

	// Comentam liniile urmatoare pentru ca vom folosi functia feof() pentru a determina finalul fisierului
	// Pastram totusi parametrul noCars si il vom incrementa in while, in cazul in care avem nevoie de numarul de masini in main

	// char buffer[LINESIZE];
	// fgets(buffer, LINESIZE, f);

	// *noCars = (int)strtol(buffer, NULL, 10);

	while (!feof(f)) {
		insertAtEnd(start, readCarFromFile(f));
		*noCars += 1;
	}

	fclose(f);

}

int main() {

	int noCars = 0;
	Node* list = NULL;

	readCarsFromFile(&list, &noCars, "cars.txt");

	parseListAndPrint(list);

	printf("\n%d cars were read from file\n", noCars);

	printf("-------------------\n");

	Car deletedCar = deleteFromBeginning(&list);

	parseListAndPrint(list);

	printf("-------------------\n");
	printf("Deleted car: \n");
	printCar(deletedCar);
	free(deletedCar.manufacturer);

	printf("-------------------\n");
	
	deletedCar = deleteFromEnd(&list);
	printf("Deleted car: \n");
	printCar(deletedCar);
	free(deletedCar.manufacturer);

	printf("-------------------\n");
	
	deletedCar = deleteFromEnd(&list);
	printf("Deleted car: \n");
	printCar(deletedCar);
	free(deletedCar.manufacturer);

	printf("-------------------\n");
	
	deletedCar = deleteFromEnd(&list);
	printf("Deleted car: \n");
	printCar(deletedCar);
	free(deletedCar.manufacturer);

	printf("-------------------\n");
	
	deletedCar = deleteFromEnd(&list);
	printf("Deleted car: \n");
	printCar(deletedCar);


	// apelurile anterioare sterg toat lista
	// refacem lista
	printf("-------------------\n");

	readCarsFromFile(&list, &noCars, "cars.txt");

	parseListAndPrint(list);

	deleteCarByManufacturer(&list, "BMW");

	printf("-------------------\n");

	parseListAndPrint(list);

	return 0;
}
