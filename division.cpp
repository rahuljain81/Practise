#include <stdio.h>

#define MAX 32

char number[MAX] = "1248163264128256512";

char quotient[MAX];

int divisor = 125;

void divide()
{
	int index = 0, qindex = 0;
	
	int num = number[index] - '0';

	while (num < divisor)
	{
		index++;
		num = num * 10 + (number[index] - '0');
	}

	printf ("%d\n", num);

	while (number[index] != '\0')
	{
		int tmp = num/divisor;

		quotient[qindex++] = tmp + '0';
		printf ("num %d tmp %d quotient %s\n", num, tmp, quotient);

		index++;

		num = (num - (tmp * divisor)) * 10 + number[index] - '0'; 
	}
}

//9985306113026052
int main()
{
	divide();
	printf ("divide %s\n", quotient);
	return 0;
}
