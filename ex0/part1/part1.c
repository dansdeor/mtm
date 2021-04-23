#include <stdio.h>
#include <stdlib.h>

/** This function Checks if the number is made by powers of 2 */
int getPowerOfTwo(int num);

int main(int argc, char const* argv[])
{
	printf("Enter size of input:\n");
	int size;
	int return_value = scanf("%d", &size);

	if (return_value != 1 || size <= 0) {
		printf("Invalid size\n");
		return 0;
	}

	printf("Enter numbers:\n");
	int* numbers = (int*) malloc(size * sizeof(int));
	if (numbers == NULL) {
		return 0;
	}

	for (int i = 0; i < size; i++) {
		return_value = scanf("%d", &numbers[i]);
		if (return_value != 1) {
			printf("Invalid number\n");
			free(numbers);
			return 0;
		}
	}

	int sum = 0;
	for (int i = 0; i < size; i++) {
		int exponent = getPowerOfTwo(numbers[i]);
		if (exponent != -1) {
			printf("The number %d is a power of 2: %d = 2^%d\n", numbers[i], numbers[i], exponent);
			sum += exponent;
		}
	}
	printf("Total exponent sum is %d\n", sum);
	free(numbers);
	return 0;
}

/**
 * @brief This function Checks if the number is made by powers of 2
 *
 * @param num The number to check
 * @return int The exponent of 2 so 2^exponent=num, or -1 if it doesn't made by powers of 2
 */
int getPowerOfTwo(int num)
{
	if (num == 1) {
		return 0;
	}
	if (num <= 0) {
		return -1;
	}
	if (num % 2 == 1) {
		return -1;
	}
	int exponent = getPowerOfTwo(num / 2);
	if (exponent == -1) {
		return -1;
	}
	return exponent + 1;
}