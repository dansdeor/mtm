#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
char* foo(char* str, int* x)
{
	char* str2;
	int i;
	x = strlen(str);
	str2 = malloc(*x);
	for (i = 0; i < *x; i++)
		str2[i] = str[*x - i];
	if (*x % 2 == 0) {
		printf("%s", str);
	}
	if (*x % 2 != 0) {
		printf("%s", str2);
	}
	return str2;
}
*/

/*
 * 1. char* str2 declared not in the same place of usage
 * 2. int i declared not in the same place of usage
 * 3. char* str type is not const and str and x are not const pointers
 * 4. x pointing type should be size_t <-----------------------------------------
 * 4. no check if str is not NULL
 * 5. no check if x in no NULL
 * 6. changing x value and not pointed variable value (dangerous!!!)
 * 7. no check after strlen that the len is bigger than 0
 * 8. the allocation size is not correct and its better to use sizeof(char) to tell the programmer what we allocating
 * 9. no check after malloc the the allocation succeeded (dangerous!!!)
 * 10. no null setting at the end of str2
 * 11. in str the indexing is incorrect (supposed to be str[*x - i - 1] dangerous!!!)
 * 12. added to for braces (needs to check if this is important or not)
 * 13. there is no reason to use both ifs if the other if checks the same statement
 * 14. added new line to both of printfs
 * 15. x is not conventional name
 * 16. str2 is not conventional name
 */

char* foo_updated(const char* const str, int* const str_length)
{
	if (NULL == str_length || NULL == str) {
		return NULL;
	}
	*str_length = strlen(str);

	char* reversed_str = malloc(sizeof(char) * (*str_length + 1));
	if (NULL == reversed_str) {
		return NULL;
	}
	reversed_str[*str_length] = '\0';

	for (int i = 0; i < *str_length; i++) {
		reversed_str[i] = str[*str_length - i - 1];
	}
	if (*str_length % 2 == 0) {
		printf("%s\n", str);
	}
	else {
		printf("%s\n", reversed_str);
	}
	return reversed_str;
}

int main(void)
{
	const char* a = "Dan";
	int x;
	char* b = foo_updated(a, &x);
	printf("%d %s\n", x, b);
	return 0;
}
