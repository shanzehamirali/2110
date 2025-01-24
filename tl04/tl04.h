#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#ifndef TL04_H
#define TL04_H

/**
 * \brief Marks unused variables
 */
#define UNUSED(x) (void)(x)

/**
 * The return values for your functions
 * \property SUCCESS
 * \property FAILURE
 */
#define SUCCESS (0)
#define FAILURE (1)


/*
* The Student struct has 2 members
* name: a pointer to a string that contains the student's name
* gpa: the student's grade point average
 */

typedef struct Student {
	char * name;
	float gpa;
} Student;

/*
* The ArrayList struct has 3 members
* current_size: the number of elements currently in the ArrayList
* capacity: the maximum number of elements the ArrayList can hold
* backing_array: a pointer to the first element in the backing array
*/

typedef struct ArrayList {
	int current_size;
	int capacity;
	Student * backing_array;
} ArrayList;

extern ArrayList *students;

int initialize_arraylist(void);
int create_student(Student * output, const char * name, const float gpa);
int add_student_to_front(const char * name, const float gpa);
int remove_student_by_name(const char * name);

#endif
