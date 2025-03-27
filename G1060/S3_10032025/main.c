#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct Car {
	int year;
	char* manufacturer;
	float cc;
};

typedef struct Car Car;

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

void readCarsFromFile(Car** carArray, int* noCars, const char* fileName) {

	FILE* f;
	f = fopen(fileName, "r");

	char buffer[LINESIZE];
	fgets(buffer, LINESIZE, f);

	*noCars = (int)strtol(buffer, NULL, 10);
	*carArray = malloc(sizeof(Car) * *noCars);

	for (int i = 0; i < (*noCars); i++) {
		(*carArray)[i] = readCarFromFile(f);
	}

	fclose(f);

}

void printCar(Car car) {
	printf("%s from %d has %5.2f\n", car.manufacturer, car.year, car.cc);
}

int main() {

	int noCars = 0;
	Car* carArray = NULL;

	

	readCarsFromFile(&carArray, &noCars, "cars.txt");

	for (int i = 0; i < noCars; i++) {
		printCar(carArray[i]);
	}

	return 0;
}

