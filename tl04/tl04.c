#include "tl04.h"
#include <stdio.h>

ArrayList *students;
int initial_capacity = 5;

/*
 * @brief Initialize the ArrayList with the initial capacity
 * DO NOT MODIFY THIS FUNCTION -- (for reference purposes only - will not affect autograder)
 */ 
int initialize_arraylist(void)
{
    students = malloc(sizeof(ArrayList));
    if (students == NULL)
    {
        return FAILURE;
    }
    students->backing_array = malloc(sizeof(Student) * initial_capacity);
    if (students->backing_array == NULL)
    {
        free(students);
        return FAILURE;
    }
    students->current_size = 0;
    students->capacity = initial_capacity;
    return SUCCESS;
}

/*
 * @brief Create a student with the given name and gpa
 *
 * @param output where the student will be stored [out variable]
 * @param name The name of the student
 * @param gpa The gpa of the student
 * @return int representing if the Student's creation was successful
 * 	- SUCCESS if the student was created successfully
 * 	- FAILURE if any parameters are invalid or malloc fails
 */
int create_student(Student *output, const char *name, const float gpa)
{
	if (output == NULL || name == NULL) {
	    return FAILURE;
	}
	if (gpa < 0 || gpa > 4) {
	    return FAILURE;
	}
    output->name = (char *)malloc(strlen(name) + 1);
    if (output->name == NULL) {
        return FAILURE;
    }
    strcpy(output->name, name);
    output->gpa = gpa;
    return SUCCESS;
}

/*
 * @brief Add the student with the given parameters to the front of the Arraylist, ensuring there is enough space in the backing array
 * Usage of create_student() is recommended, but not required.
 *
 * @param name The name of the student
 * @param gpa The gpa of the student
 * @return int representing if the Student was added successfully
 * 	- SUCCESS if the student was added successfully
 * 	- FAILURE if any parameters are invalid, malloc fails or the students arraylist is NULL
 */
int add_student_to_front(const char *name, const float gpa)
{
    if (students->current_size >= students->capacity) {
        // Double the capacity
        int new_capacity = students->capacity * 2;
        // Reallocate memory for backing_array
        Student *new_array = (Student *)realloc(students->backing_array, new_capacity * sizeof(Student));
        if (new_array == NULL) {
            free(new_array);
            return FAILURE; // realloc failed
        }
        students->backing_array = new_array;
        students->capacity = new_capacity;
    }

    // Create a new student record
    Student new_student;
    int result = create_student(&new_student, name, gpa);
    if (result == FAILURE) {
        return FAILURE; // Failed to create student record
    }

    // Shift elements to make room for the new student at the front
    for (int i = students->current_size; i > 0; i--) {
        students->backing_array[i] = students->backing_array[i - 1];
    }

    // Insert the new student at the beginning
    students->backing_array[0] = new_student;

    // Update current_size
    students->current_size++;

    return SUCCESS; // Student added successfully
}

/*
 * @brief Remove a student from the Arraylist and leaving a blank space at the end
 * @param name the name of the student to remove
 * @return int representing if the Student was removed successfully
 * 	- SUCCESS if the student was removed successfully
 * 	- FAILURE if any parameters are invalid, the student is not found or the students arraylist is NULL
 */
int remove_student_by_name(const char *name)
{
	if (name == NULL || students == NULL) {
	    return FAILURE;
	}
	    int found_index = -1;
        for (int i = 0; i < students->current_size; i++) {
            if (strcmp(students->backing_array[i].name, name) == 0) {
                found_index = i;
                break;
            }
        }

        // If student not found, return FAILURE
        if (found_index == -1) {
            return FAILURE;
        }

        // Shift elements to fill the gap left by removing the student
        for (int i = found_index; i < students->current_size - 1; i++) {
            students->backing_array[i] = students->backing_array[i + 1];
        }

        // Decrease the number of students
        students->current_size--;

        return SUCCESS;

}
