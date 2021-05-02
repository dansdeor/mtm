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
 */

char* foo_updated(const char* const str, int* const x)
{
	if (NULL == x || NULL == str) {
		return NULL;
	}
	*x = strlen(str);

	char* str2 = malloc(sizeof(char) * (*x + 1));
	if (NULL == str2) {
		return NULL;
	}
	str2[*x] = '\0';

	for (int i = 0; i < *x; i++) {
		str2[i] = str[*x - i - 1];
	}
	if (*x % 2 == 0) {
		printf("%s\n", str);
	}
	else {
		printf("%s\n", str2);
	}
	return str2;
}

int main(void)
{
	const char* a = "Dan";
	int x;
	char* b = foo_updated(a, &x);
	printf("%d %s\n", x, b);
	return 0;
}
