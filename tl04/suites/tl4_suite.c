/**
 * @file tl4_suite.c
 * @author  Rohan, Toby, Jonathan, Richard
 * @brief Testing Suites to TL4 - Spring 2024
 * @date 2024-04-15
 */

// Check Docs
// Tutorial : https://libcheck.github.io/check/doc/check_html/check_3.html
// Check API: https://libcheck.github.io/check/doc/doxygen/html/check_8h.html

// System Headers
#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/wait.h> // For grabbing return value of system call

// TA Headers
#include "fakemalloc.h"
#include "test_utils.h"

// The number of mallocs in user code until the next one fails, or -1 for
// successful mallocs
long long mallocs_until_fail = LLONG_MAX;
long long bytes_malloced_until_fail = LLONG_MAX;

static void reset_malloc_limits(void)
{
    mallocs_until_fail = LLONG_MAX;
    bytes_malloced_until_fail = LLONG_MAX;
}

START_TEST(test_create_student_null_output)
{
    ck_assert_msg(create_student(NULL, "A ghost", 3.3) == FAILURE,
                  "create_student should return FAILURE when given NULL output");
}
END_TEST

START_TEST(test_create_student_null_name)
{
    Student s;
    ck_assert_msg(create_student(&s, NULL, 3.3) == FAILURE,
                  "create_student should return FAILURE when given NULL name");
}
END_TEST

START_TEST(test_create_student_out_of_range_gpa)
{
    Student gt = {"So close to perfection", 3.999999999};
    Student s = gt;
    ck_assert_msg(create_student(&s, "Probably a cheater", 4.00001) == FAILURE,
                  "create_student should return FAILURE when given gpa larger "
                  "than 4.0");
    ck_assert_msg(s.name == gt.name && s.gpa == gt.gpa, "create_student should not modify output on failure");
    ck_assert_msg(create_student(&s, "i can't think of a funny name", -0.000001) == FAILURE,
                  "create_student should return FAILURE when given gpa smaller "
                  "than 0.0");
    ck_assert_msg(s.name == gt.name && s.gpa == gt.gpa, "create_student should not modify output on failure");
}
END_TEST

START_TEST(test_create_student_malloc_failure)
{
    mallocs_until_fail = 0;
    Student s = {NULL, 0};
    Student gt = s;
    ck_assert_msg(create_student(&s, "Average Joe", 3.0) == FAILURE,
                  "create_student should FAILURE on malloc failure");
    ck_assert_msg(s.name == gt.name && s.gpa == gt.gpa, "create_student should not modify output on failure");
}

START_TEST(test_create_student)
{
    Student s = {NULL, 0};
    const char *name = "Average Joe";
    ck_assert_msg(create_student(&s, name, 3.0) == SUCCESS,
                  "create_student should return SUCCESS on success");
    ck_assert_msg(s.name, "student name was NULL, expected an allocated array");
    ck_assert_msg(s.name != name,
                  "create_student should copy the name instead of reusing the "
                  "name pointer passed in");
    ck_assert_msg(strcmp(s.name, name) == 0,
                  "returned student name is \"%s\", expected \"%s\"",
                  s.name, name);
    ck_assert_msg(s.gpa == 3.0, "returned student gpa is %f, expected %f",
                  s.gpa, 3.0);
    free(s.name);

    s = (struct Student){NULL, 0};
    const char *name2 = "This string has exactly 99 characters. Don't believe me? I promise it's true. I measured it myself!";
    ck_assert_msg(create_student(&s, name2, 3.0) == SUCCESS,
                  "create_student should allow names of length MAX_NAME_LENGTH");
    ck_assert_msg(s.name, "student name was NULL, expected an allocated array");
    ck_assert_msg(s.name != name2,
                  "create_student should copy the name instead of reusing the "
                  "name pointer passed in");
    ck_assert_msg(strcmp(s.name, name2) == 0, "returned student name is \"%s\", expected \"%s\"",
                  s.name, name2);
    ck_assert_msg(s.gpa == 3.0, "returned student gpa is %f, expected %f",
                  s.gpa, 3.0);
    free(s.name);

    s = (struct Student){NULL, 0};
    const char *name3 = "ouch";
    ck_assert_msg(create_student(&s, name3, 0.0) == SUCCESS,
                  "create_student should allow gpa == 0.0");
    ck_assert_msg(s.name, "student name was NULL, expected an allocated array");
    ck_assert_msg(s.name != name3,
                  "create_student should copy the name instead of reusing the "
                  "name pointer passed in");
    ck_assert_msg(strcmp(s.name, name3) == 0, "returned student name is \"%s\", expected \"%s\"",
                  s.name, name3);
    ck_assert_msg(s.gpa == 0.0, "returned student gpa is %f, expected %f",
                  s.gpa, 0.0);
    free(s.name);

    s = (struct Student){NULL, 0};
    const char *name4 = "Mr. Perfect";
    ck_assert_msg(create_student(&s, name4, 4.0) == SUCCESS,
                  "create_student should allow gpa == 4.0");
    ck_assert_msg(s.name, "student name was NULL, expected an allocated array");
    ck_assert_msg(s.name != name4,
                  "create_student should copy the name instead of reusing the "
                  "name pointer passed in");
    ck_assert_msg(strcmp(s.name, name4) == 0, "returned student name is \"%s\", expected \"%s\"",
                  s.name, name4);
    ck_assert_msg(s.gpa == 4.0, "returned student gpa is %f, expected %f",
                  s.gpa, 4.0);
    free(s.name);
}
END_TEST

START_TEST(test_remove_student_null_students)
{
    students = NULL;
    ck_assert_msg(remove_student_by_name("Bobby Tables") == FAILURE,
                  "remove_student_by_name must return FAILURE when students "
                  "is NULL");
}
END_TEST

START_TEST(test_remove_student_null_name)
{
    ArrayList gt = {0, 0, NULL};
    _initialize_students();
    _push_student("Stop reading", 3, students);
    _push_student("these stupid names", 3, students);
    _push_student("and get back to", 3, students);
    _push_student("the timed lab!", 3, students);
    _push_student("Stop reading", 3, &gt);
    _push_student("these stupid names", 3, &gt);
    _push_student("and get back to", 3, &gt);
    _push_student("the timed lab!", 3, &gt);

    ck_assert_msg(remove_student_by_name(NULL) == FAILURE,
                  "remove_student_by_name must return FAILURE when student name "
                  "is NULL");
    _check_arraylist(students, &gt,
                     "remove_student_by_name should not alter students on "
                     "failure:");
    _free_students(students);
    free(students);
    _free_students(&gt);
}
END_TEST

START_TEST(test_remove_student_not_found)
{
    ArrayList gt = {0, 0, NULL};
    _initialize_students();
    _push_student("Stop reading", 3, students);
    _push_student("these stupid names", 3, students);
    _push_student("and get back to", 3, students);
    _push_student("the timed lab!", 3, students);
    _push_student("Stop reading", 3, &gt);
    _push_student("these stupid names", 3, &gt);
    _push_student("and get back to", 3, &gt);
    _push_student("the timed lab!", 3, &gt);

    ck_assert_msg(remove_student_by_name("Bobby Tables") == FAILURE,
                  "remove_student_by_name must return FAILURE when no student "
                  "with the given name is found in the students array");
    _check_arraylist(students, &gt,
                     "remove_student_by_name should not alter students on "
                     "failure:");
    _free_students(students);
    free(students);
    _free_students(&gt);
}
END_TEST

START_TEST(test_remove_only_student)
{
    ArrayList gt = {0, 0, NULL};
    _initialize_students();
    _push_student("Bobby Tables", 3, students);

    ck_assert_msg(remove_student_by_name("Bobby Tables") == SUCCESS,
                  "remove_student_by_name should succeed when the student "
                  "is found in the array");
    _check_arraylist(students, &gt, "after removing the student");
    _free_students(students);
    free(students);
    _free_students(&gt);
}
END_TEST

START_TEST(test_remove_student_from_end)
{
    ArrayList gt = {0, 0, NULL};
    _initialize_students();
    _push_student("Stop reading", 3, students);
    _push_student("these stupid names", 3, students);
    _push_student("and get back to", 3, students);
    _push_student("the timed lab!", 3, students);
    _push_student("Stop reading", 3, &gt);
    _push_student("these stupid names", 3, &gt);
    _push_student("and get back to", 3, &gt);
    //_push_student("the timed lab!", 3, &gt);

    ck_assert_msg(remove_student_by_name("the timed lab!") == SUCCESS,
                  "remove_student_by_name should succeed when the student "
                  "is found in the array");
    _check_arraylist(students, &gt, "after removing the student");
    _free_students(students);
    free(students);
    _free_students(&gt);
}
END_TEST

START_TEST(test_remove_student_from_front)
{
    ArrayList gt = {0, 0, NULL};
    _initialize_students();
    _push_student("Stop reading", 3, students);
    _push_student("these stupid names", 3, students);
    _push_student("and get back to", 3, students);
    _push_student("the timed lab!", 3, students);
    //_push_student("Stop reading", 3, &gt);
    _push_student("these stupid names", 3, &gt);
    _push_student("and get back to", 3, &gt);
    _push_student("the timed lab!", 3, &gt);

    ck_assert_msg(remove_student_by_name("Stop reading") == SUCCESS,
                  "remove_student_by_name should succeed when the student "
                  "is found in the array");
    _check_arraylist(students, &gt, "after removing the student");
    _free_students(students);
    free(students);
    _free_students(&gt);
}
END_TEST

START_TEST(test_remove_student_from_middle)
{
    ArrayList gt = {0, 0, NULL};
    _initialize_students();
    _push_student("Stop reading", 3, students);
    _push_student("these stupid names", 3, students);
    _push_student("and get back to", 3, students);
    _push_student("the timed lab!", 3, students);
    _push_student("Stop reading", 3, &gt);
    //_push_student("these stupid names", 3, &gt);
    _push_student("and get back to", 3, &gt);
    _push_student("the timed lab!", 3, &gt);

    ck_assert_msg(remove_student_by_name("these stupid names") == SUCCESS,
                  "remove_student_by_name should succeed when the student "
                  "is found in the array");
    _check_arraylist(students, &gt, "after removing the student");
    _free_students(students);
    free(students);
    _free_students(&gt);
}
END_TEST

// ================== add_student_to_front tests ==================== (Toby) ====================
START_TEST(test_add_student_to_front_empty)
{
    ArrayList gt = {0, 0, NULL};
    _initialize_students();

    _push_student("George P Burdell", 4.0, &gt);

    ck_assert_msg(add_student_to_front("George P Burdell", 4.0) == SUCCESS,
                  "add_student_to_front on empty list should succeed given valid arguements and no malloc failure");
    _check_arraylist(students, &gt, "after adding only student");

    _free_students(students);
    free(students);
    _free_students(&gt);
}
END_TEST

START_TEST(test_add_student_to_front_nonempty)
{
    ArrayList gt = {0, 0, NULL};
    _initialize_students();
    // _add_student("a", 3, students); -- added in test
    _push_student("b", 3, students);
    _push_student("c", 3, students);
    _push_student("d", 3, students);
    _push_student("e", 3, students);
    _push_student("f", 3, students);

    _push_student("a", 3, &gt);
    _push_student("b", 3, &gt);
    _push_student("c", 3, &gt);
    _push_student("d", 3, &gt);
    _push_student("e", 3, &gt);
    _push_student("f", 3, &gt);

    ck_assert_msg(add_student_to_front("a", 3) == SUCCESS,
                  "add_student_to_front on nonempty list should succeed given valid arguements and no malloc failure");
    _check_arraylist(students, &gt, "after adding student to front");

    _free_students(students);
    free(students);
    _free_students(&gt);
}
END_TEST

START_TEST(test_add_student_to_front_null_students)
{
    students = NULL; // valgrind requires this (even though standard C compilation sets uninitialized globals to 0 / NULL)
                     // because global zero-initialization can be turned off with a flag

    ck_assert_msg(add_student_to_front("Student", 2.0) == FAILURE, "When students = NULL, add_student_to_front should return FAILURE");
    ck_assert_msg(students == NULL, "students should stay unchanged when add_student_to_front is called with students = NULL");
}
END_TEST

// add_student_to_help failure helper
void add_to_front_typical_failure_test(char *cond_str, char *name, double gpa)
{
    ArrayList gt = {0, 0, NULL};
    _initialize_students();
    // _add_student(..., ..., students); -- added in test (will fail)
    _push_student("b", 3, students);
    _push_student("c", 3, students);
    _push_student("d", 3, students);
    _push_student("e", 3, students);
    _push_student("f", 3, students);

    _push_student("b", 3, &gt);
    _push_student("c", 3, &gt);
    _push_student("d", 3, &gt);
    _push_student("e", 3, &gt);
    _push_student("f", 3, &gt);

    ck_assert_msg(add_student_to_front(name, gpa) == FAILURE,
                  "add_student_to_front should return FAILURE given %s", cond_str);

    char msgBuf[200];
    snprintf(msgBuf, 200, "after failing to add student to front due to %s", cond_str);
    _check_arraylist(students, &gt, msgBuf);

    _free_students(students);
    free(students);
    _free_students(&gt);
}

START_TEST(test_add_student_to_front_null_name)
{
    add_to_front_typical_failure_test("null name", NULL, 3.0);
}
END_TEST

START_TEST(test_add_student_to_front_invalid_gpa)
{
    add_to_front_typical_failure_test("null name", "Joe", -0.01);
}
END_TEST

START_TEST(test_add_student_to_front_malloc_failure)
{
    ArrayList gt = {0, 0, NULL};
    _initialize_students();
    // _add_student("a", 3, students); -- added in test (will fail)
    _push_student("b", 3, students);
    _push_student("c", 3, students);
    _push_student("d", 3, students);
    _push_student("e", 3, students);
    _push_student("f", 3, students);

    _push_student("b", 3, &gt);
    _push_student("c", 3, &gt);
    _push_student("d", 3, &gt);
    _push_student("e", 3, &gt);
    _push_student("f", 3, &gt);

    mallocs_until_fail = 0;
    ck_assert_msg(add_student_to_front("a", 3) == FAILURE,
                  "add_student_to_front should return FAILURE given malloc/realloc failure");
    _check_arraylist(students, &gt, "after failing to add student to front due to malloc/realloc failure");

    _free_students(students);
    free(students);
    _free_students(&gt);
}
END_TEST

START_TEST(test_add_student_to_front_malloc_failure_after_malloc_success)
{
    ArrayList gt = {0, 0, NULL};
    _initialize_students();
    // _add_student("a", 3, students); -- added in test (will fail)
    _push_student("b", 3, students);
    _push_student("c", 3, students);
    _push_student("d", 3, students);
    _push_student("e", 3, students);
    _push_student("f", 3, students);

    _push_student("b", 3, &gt);
    _push_student("c", 3, &gt);
    _push_student("d", 3, &gt);
    _push_student("e", 3, &gt);
    _push_student("f", 3, &gt);

    mallocs_until_fail = 1;
    ck_assert_msg(add_student_to_front("a", 3) == FAILURE,
                  "add_student_to_front should return FAILURE given malloc/realloc failure");
    _check_arraylist(students, &gt, "after failing to add student to front due to malloc/realloc failure");

    _free_students(students);
    free(students);
    _free_students(&gt);
}
END_TEST

// COVERAGE TESTS ====================================================================================================
START_TEST(test_coverage_1)
{
    ArrayList gt;
    _initialize_students();

    for (char c = 'k'; c >= 'a'; c--)
    {
        char c_str[] = {c, '\0'};
        ck_assert_msg(add_student_to_front(c_str, 1) == SUCCESS, "add_student_to_front should succeed after normal _initialize_students");
    }

    gt = (ArrayList){0, 0, NULL};
    _push_student("a", 1, &gt);
    _push_student("b", 1, &gt);
    _push_student("c", 1, &gt);
    _push_student("d", 1, &gt);
    _push_student("e", 1, &gt);
    _push_student("f", 1, &gt);
    _push_student("g", 1, &gt);
    _push_student("h", 1, &gt);
    _push_student("i", 1, &gt);
    _push_student("j", 1, &gt);
    _push_student("k", 1, &gt);

    _check_arraylist(students, &gt, "after adding 11 elements");

    _free_students(&gt);
    gt = (ArrayList){0, 0, NULL};
    _push_student("b", 1, &gt);
    _push_student("c", 1, &gt);
    _push_student("i", 1, &gt);
    _push_student("j", 1, &gt);

    char *to_remove[] = {"f", "e", "h", "g", "a", "d", "k"};
    for (int i = 0; i < 7; i++)
    {
        ck_assert_msg(remove_student_by_name(to_remove[i]) == SUCCESS, "after adding 11 students, removing %d-th student (name = %s) should succeed, but it failed :(", (i + 1), to_remove[i]);
    }

    // wait, we wanted "a" still :() -- (he's back but stronger!)
    int add_res = add_student_to_front("a", 2);
    ck_assert_msg(add_res == SUCCESS, "adding student 'a' back should succeed");

    add_student_to_front("v", 0.0001); // is that a Vy reference?
    ck_assert_msg(add_res == SUCCESS, "adding student 'v' should succeed");
    add_student_to_front("v", 4); // his twin brother Viswanathan Anand too? -- the lineup is crazy :O
    ck_assert_msg(add_res == SUCCESS, "adding another student 'v' should succeed");

    _free_students(&gt);
    gt = (ArrayList){0, 0, NULL};
    _push_student("v", 4, &gt);
    _push_student("v", 0.0001, &gt);
    _push_student("a", 2, &gt);
    _push_student("b", 1, &gt);
    _push_student("c", 1, &gt);
    _push_student("i", 1, &gt);
    _push_student("j", 1, &gt);

    _check_arraylist(students, &gt, "after adding 11 elements, then removing 7, then adding 3 back (including duplicates)");

    _free_students(students);
    free(students);
    _free_students(&gt);
}
END_TEST

START_TEST(test_coverage_2)
{
    ArrayList gt;
    _initialize_students();

    char *some_tas[] = {"Gilbert", "Vy", "Daring", "Toby", "Gal", "Richard", "Rohan", "Jonathan", "Nathan", "Gilbert"};
    int initial_num_tas = 10;
    for (int i = 0; i < initial_num_tas; i++)
    {
        char *name = some_tas[initial_num_tas - i - 1];
        ck_assert_msg(add_student_to_front(name, 4.0) == SUCCESS, "%d-th TA addition (name = '%s'), ie add_student_to_front, should work >:O", (i + 1), name);
    }

    gt = (ArrayList){0, 0, NULL};
    _push_student("Gilbert", 4, &gt);
    _push_student("Vy", 4, &gt);
    _push_student("Daring", 4, &gt);
    _push_student("Toby", 4, &gt);
    _push_student("Gal", 4, &gt);
    _push_student("Richard", 4, &gt);
    _push_student("Rohan", 4, &gt);
    _push_student("Jonathan", 4, &gt);
    _push_student("Nathan", 4, &gt);
    _push_student("Gilbert", 4, &gt);

    _check_arraylist(students, &gt, "after adding 10 TAs (1 duplicate)");

    // fix Darren typo oops
    free(students->backing_array[2].name);
    ck_assert_msg(create_student(&students->backing_array[2], "Darren", 4) == SUCCESS, "Using create_student in-place in students->backing_array should produce SUCCESS, given correct arguments & malloc working");

    ck_assert_msg(remove_student_by_name("Gilbert") == SUCCESS, "Removing first student with name = 'Gilbert' should succeed");
    ck_assert_msg(remove_student_by_name("Gilbert") == SUCCESS, "Removing second student with name = 'Gilbert' should succeed");
    ck_assert_msg(remove_student_by_name("Gilbert") == FAILURE, "Removing third student with name = 'Gilbert' should fail, because at this point, there is none");

    ck_assert_msg(remove_student_by_name("Toby") == SUCCESS, "Removing student with name = 'Toby' should succeed");

    _free_students(&gt);
    gt = (ArrayList){0, 0, NULL};
    _push_student("Vy", 4, &gt);
    _push_student("Darren", 4, &gt);
    _push_student("Gal", 4, &gt);
    _push_student("Richard", 4, &gt);
    _push_student("Rohan", 4, &gt);
    _push_student("Jonathan", 4, &gt);
    _push_student("Nathan", 4, &gt);

    _check_arraylist(students, &gt, "after adding 10 TAs (1 duplicate), then removing 3 (including both duplicates)");

    _free_students(students);
    free(students);
    _free_students(&gt);
}
END_TEST

Suite *tl4_suite(void)
{
    Suite *s = suite_create("tl4_suite");

    // create student tests
    tcase_singleton(s, reset_malloc_limits, NULL, test_create_student_null_output);
    tcase_singleton(s, reset_malloc_limits, NULL, test_create_student_null_name);
    tcase_singleton(s, reset_malloc_limits, NULL, test_create_student_out_of_range_gpa);
    tcase_singleton(s, reset_malloc_limits, NULL, test_create_student_malloc_failure);
    tcase_singleton(s, reset_malloc_limits, NULL, test_create_student);

    // remove tests
    tcase_singleton(s, reset_malloc_limits, NULL, test_remove_student_null_name);
    tcase_singleton(s, reset_malloc_limits, NULL, test_remove_student_null_students);
    tcase_singleton(s, reset_malloc_limits, NULL, test_remove_student_not_found);
    tcase_singleton(s, reset_malloc_limits, NULL, test_remove_only_student);
    tcase_singleton(s, reset_malloc_limits, NULL, test_remove_student_from_end);
    tcase_singleton(s, reset_malloc_limits, NULL, test_remove_student_from_front);
    tcase_singleton(s, reset_malloc_limits, NULL, test_remove_student_from_middle);

    // add tests
    tcase_singleton(s, reset_malloc_limits, NULL, test_add_student_to_front_null_students);
    tcase_singleton(s, reset_malloc_limits, NULL, test_add_student_to_front_null_name);
    tcase_singleton(s, reset_malloc_limits, NULL, test_add_student_to_front_invalid_gpa);
    tcase_singleton(s, reset_malloc_limits, NULL, test_add_student_to_front_empty);
    tcase_singleton(s, reset_malloc_limits, NULL, test_add_student_to_front_nonempty);
    tcase_singleton(s, reset_malloc_limits, NULL, test_add_student_to_front_malloc_failure);
    tcase_singleton(s, reset_malloc_limits, NULL, test_add_student_to_front_malloc_failure_after_malloc_success);

    // coverage tests
    tcase_singleton(s, reset_malloc_limits, NULL, test_coverage_1);
    tcase_singleton(s, reset_malloc_limits, NULL, test_coverage_2);

    return s;
}
