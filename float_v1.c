#include <stdio.h>

// Gives a wrong answer due to %d for int being used
void ex_1()
  {
	float result;
	result = 7.0/22.0;
	printf("The result is %d\n", result);
  }

void ex_2(){
	float result;
	result = 7.0/22.0;
	printf("The result is %f\n", result);
	}

int main()
  {
	ex_1();
	ex_2();
  }

