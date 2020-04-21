
/**
 * @file my_string.c
 * @author Saumya Jain
 * @brief Your implementation of these famous 3 string.h libraries!
 * 
 * NOTE: NO ARRAY NOTATION IS ALLOWED IN THIS FILE
 * 
 * @date 2020-03-10
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <stddef.h>
#include "hw7.h"

/**
 * @brief Calculate the length of a string
 * 
 * @param s a constant C string
 * @return size_t the number of characters in the passed in string
 */
size_t my_strlen(const char *s)
{
	const char* curr = s;
	int length = 0;

	while (*curr != '\0') {
		length++;
		curr++;
	}

	return length;
}

/**
 * @brief Compare two strings
 * 
 * @param s1 First string to be compared
 * @param s2 Second string to be compared
 * @param n First (at most) n bytes to be compared
 * @return int "less than, equal to, or greater than zero if s1 (or the first n bytes thereof) is found, respectively, to be less than, to match, or be greater than s2"
 */
int my_strncmp(const char *s1, const char *s2, size_t n)
{
    while(n-- > 0) {
		unsigned char char1 = (unsigned char) *s1++;
		unsigned char char2 = (unsigned char) *s2++;

		if (char1 != char2)
		{
			return char1 - char2;
		}
		if (char1 == '\0')
		{
			return 0;
		}
		if (char2 == '\0') {
			return 0;
		}
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
    char *copy = dest;
	while (n-- != 0 && (*dest++ = *src++) != '\0') {
		// no need to do anything
	}

	return copy;
}
