#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Student {
	int studentID;
	char* name;
	int noGrades;
	float* grades;
};

typedef struct Student Student;

Student createStudent(int studentID, const char* name, int noGrades, float* grades) {

	Student s;

	s.studentID = studentID;

	s.name = malloc((strlen(name) + 1) * sizeof(char));

	strcpy(s.name, name);

	s.noGrades = noGrades;

	s.grades = malloc(noGrades * sizeof(float));

	for (int i = 0; i < noGrades; i++) {
		s.grades[i] = grades[i];
	}

	return s;
}

Student* createPStudent(int studentID, const char* name, int noGrades, float* grades) {

	Student* s = malloc(sizeof(Student));

	// (*s).studentID = studentID;
	if (s != NULL) {
		s->studentID = studentID;
		s->name = malloc((strlen(name) + 1) * sizeof(char));

		strcpy(s->name, name);

		s->noGrades = noGrades;

		s->grades = malloc(noGrades * sizeof(float));

		for (int i = 0; i < noGrades; i++) {
			s->grades[i] = grades[i];
		}

	}

	return s;
}

void printStudent(Student s) {
	printf("%d %s: ", s.studentID, s.name);
	for (int i = 0; i < s.noGrades; i++) {
		printf("%5.2f ", s.grades[i]);
	}
	printf("\n");
}

void modifyStudent(Student* s) {

	int newID;
	scanf("%d", &newID);

	char buffer[50];
	scanf("%s", buffer);

	/*free(s->name);
	s->name = malloc((strlen(buffer) + 1) * sizeof(char));*/

	strcpy(s->name, buffer);

	s->studentID = newID;

}

int main() {

	/*float studGrades[3] = {5.6, 7.8, 10.0};
	struct Student stud = { .studentID = 1, .name = "John", .grades = studGrades}*/

	float studGrades[3] = { 5.6, 7.8, 10.0 };
	Student stud = createStudent(1, "John", 3, studGrades);

	printStudent(stud);
	printf("\n-----------\n");

	Student vStud[3];
	vStud[0] = createStudent(1, "John", 3, studGrades);
	vStud[1] = createStudent(2, "Mark", 3, studGrades);
	vStud[2] = createStudent(3, "Luke", 3, studGrades);

	Student stud1 = createStudent(4, "Mary", 3, studGrades);

	Student* pStud = createPStudent(5, "Jane", 3, studGrades);

	Student** vPStud = malloc(4 * sizeof(Student*));

	vPStud[0] = &stud1;
	vPStud[1] = pStud;
	vPStud[2] = &vStud[2];

	vStud[2].studentID = 100;
 
	for (int i = 0; i < 3; i++) {
		printStudent(*vPStud[i]);
	}

	printf("\n-----------\n");

	modifyStudent(&vStud[0]);
	printStudent(stud1);
}
