
#include <check.h>
#include <stddef.h>
#include <stdio.h>
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define RETURN_ERROR_VALUE -100

// Suites
extern Suite *tl4_suite(void);

// Define a check containing only one test case of the same name
#define tcase_singleton(suite, setup_fixture, teardown_fixture, func)   \
    {                                                                   \
        TCase *tc = tcase_create(STRINGIFY(func));                      \
        tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
        tcase_add_test(tc, func);                                       \
        suite_add_tcase(s, tc);                                         \
    }

/******************************************************************************/
/**************************** tl4 Header Info *********************************/
/******************************************************************************/

#define DEBUG_FLAG "-d"

#include "../tl04.h"

int _initialize_students(void);
void _push_student(char *name, float gpa, ArrayList *students);
void _check_arraylist(ArrayList *actual, ArrayList *expected, char *pfx);
void _free_students(ArrayList *al);

// helpers
// extern void _reset_students(void);
// extern int _initialize_students(void);
// extern int _add_student_simple(const char* name, const double gpa);
// extern void _add_students(Student arr[], int num);

// extern const char *questions[7];
// extern void _initialize_stack(int _capacity);
// extern int _stack_push(const char *question, enum category_t category);
// extern int _stack_pop(struct post_t *data);
// extern int _destroy_stack(void);
