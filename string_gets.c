#include <stdio.h>

void get_ex()
  {
	char array1[50];
	char *array2;

	printf("Now enter another string less than 50");
	printf(" characters with spaces: \n\n");
	gets(array1);

	printf("\nYou entered: ");
	puts(array1);

	printf("\nTry again: ")
	scanf("%s", array2);
  }
