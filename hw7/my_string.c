/**
 * @file my_string.c
 * @author Shanzeh Amirali
 * @brief Your implementation of the famous string.h library functions!
 *
 * NOTE: NO ARRAY NOTATION IS ALLOWED IN THIS FILE
 *
 * @date 2024-03-xx
 */

#include "my_string.h"

/* Note about UNUSED_PARAM
*
* UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
* parameters prior to implementing the function. Once you begin implementing this
* function, you can delete the UNUSED_PARAM lines.
*/

/**
 * @brief Calculate the length of a string
 *
 * @param s a constant C string
 * @return size_t the number of characters in the passed in string
 */
size_t my_strlen(const char *s)
{
    size_t len = 0;
    while(*s != '\0') {
        len++;
        s++;
    }
    return len;
}

/**
 * @brief Compare two strings
 *
 * @param s1 First string to be compared
 * @param s2 Second string to be compared
 * @param n First (at most) n bytes to be compared
 * @return int representing the difference between the strings:
 *          - 0 if the strings are equal
 *          - arbitrary positive number if s1 > s2
 *          - arbitrary negative number if s1 < s2
 */
int my_strncmp(const char *s1, const char *s2, size_t n)
{
    for (size_t i = 0; i < n && (*s1 != '\0' || *s2 != '\0'); ++i) {
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        ++s1;
        ++s2;
    }
    return 0;
}

/**
 * @brief Copy a string
 *
 * @param dest The destination buffer
 * @param src The source to copy from
 * @param n maximum number of bytes to copy
 * @return char* a pointer same as dest
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i = 0;
    while (i < n) {
        if (*(src + i) != '\0') *(dest + i) = *(src + i);
        else *(dest + i) = '\0';
        i++;
    }
    return dest;
}

/**
 * @brief Concatenates two strings and stores the result
 * in the destination string
 *
 * @param dest The destination string
 * @param src The source string
 * @param n The maximum number of bytes (or characters) from src to concatenate
 * @return char* a pointer same as dest
 */
char *my_strncat(char *dest, const char *src, size_t n)
{
    char *orig = dest;
    while (*dest != '\0') {
        dest++;
    }
    for (size_t i = 0; i < n && *src != '\0'; ++i) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return orig;
}

/**
 * @brief Copies the character c into the first n
 * bytes of memory starting at *str
 *
 * @param str The pointer to the block of memory to fill
 * @param c The character to fill in memory
 * @param n The number of bytes of memory to fill
 * @return char* a pointer same as str
 */
void *my_memset(void *str, int c, size_t n)
{
    size_t i = 0;
    char *s = str;
    while (i < n) {
        *(s + i) = (char) c;
        i++;
    }
    return s;
}

/**
 * @brief Checks whether the string is a palindrome
 * (i.e., reads the same forwards and backwards)
 * assuming that the case of letters is irrelevant.
 * 
 * @param str The pointer to the string
 * @return 1 if the string is a palindrome,
 * or 0 if the string is not
*/
int is_palindrome_ignore_case(const char *str) 
{
    const char *start = str;
    const char *end = str;

    while (*end != '\0') {
        end++;
    }
    end--;
    while (start < end) {
        char chr1 = *(start);
        char chr2 = *(end);
        if (chr1 >= 'a') {
            chr1 -= 32;
        } if (chr2 >= 'a') {
            chr2 -= 32;
        }
        if (chr1 != chr2) {
            return 0;
        } else {
            start++;
            end--;
        }
    }
    return 1;
}

/**
 * @brief Apply a Caesar shift to each character
 * of the provided string in place.
 * 
 * @param str The pointer to the string
 * @param shift The amount to shift by
*/
void caesar_shift(char *str, int shift) 
{
    int new_char;
    while (*str != '\0') {
        if (*str >= 'A' && *str <= 'Z') {
            new_char = (*str - 'A' + shift) % 26 + 'A';
        } else if (*str >= 'a' && *str <= 'z') {
            new_char = (*str - 'a' + shift) % 26 + 'a';
        } else {
            new_char = *str;
        }
        *str = new_char;
        str++;
    }
}

/**
 * @brief Mutate the string in-place to
 * remove duplicate characters that appear
 * consecutively in the string.
 * 
 * @param str The pointer to the string
*/
void deduplicate_str(char *str) 
{
    char *write = str;
    while (*str != '\0') {
        *write = *str;
        while (*str != '\0' && *str == *(str + 1)) {
            str++;
        }
        str++;
        write++;
    }
    *write = '\0';
}

/**
 * @brief Swap the position of
 * two strings in memory.
 * 
 * @param s1 The first string
 * @param s2 The second string
*/
void swap_strings(char **s1, char **s2) 
{
    char *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}