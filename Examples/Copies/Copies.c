#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	// Copy method 1:
	int a1 = 10, b1 = 0;
	printf("Before: [a1=%d, b1=%d]\n", a1, b1);
	b1 = a1; // First type of copy
	printf("After: [a1=%d, b1=%d]\n\n", a1, b1);

	// Copy method 2:
	int a2 = 10, b2 = 0;
	printf("Before: [a2=%d, b2=%d]\n", a2, b2);
	memcpy(&b2, &a2, sizeof(a2)); // Second type of copy
	printf("After: [a2=%d, b2=%d]\n\n", a2, b2);

	// Pointers copy:
	int *x;
	*x = 10;
	int *y = x;

	printf("After 'free()': [*x=%d, *y=%d]\n", *x, *y);


	free(y);

	printf("Before 'free()': [*x=%d, *y=%d]\n", *x, *y); // Strange numbers will print out

	return 0;
}
