#if 0
#include <stdio.h>
#endif
#define printf(...) //printf(...)

#define MAX	25

char input[MAX];
char str1[MAX * 500000];
char str2[MAX * 500000];

int size1, size2, input_size, move;
int count;
int input_count, move_count;

int my_strlen(char ch[])
{
	int i;
	for (i=0; ch[i] != '\0'; i++)
		;
	return i;
}

void init()
{
	size1 = size2 = input_size = 0;
	str1[0] = str2[0] = '\0';
	move = 0;
	count = 0;
	move_count = input_count = 0;
}
void cmd_input(char ch[])
{
	count++;
	input_count = count;
	input_size = my_strlen(ch);

	printf ("input [%s] size [%d]\n", ch, input_size);

	int i;
	for ( i=0; i < input_size; i++)
	{
		str1[size1 + i] = ch[i];
		input[i] = ch[i];
	}
	str1[size1 + i]  = '\0';
	input[i] = '\0';

	if (size1 == 0)
	{
		size2 = 0;
		str2[0] = '\0';
	}
	size1 += input_size;
	//move = 0;
	printf ("Input) str1 [%s] size1 %d str2[%s] size2 %d\n", str1, size1, str2, size2);
	
	if (my_strlen (str1) != size1)
		printf ("ERROR 1: %d %d\n", my_strlen(str1), size1);
	if (my_strlen (str2) != size2)
		printf ("ERROR 2: %d %d\n", my_strlen(str2), size2);
}

void cmd_movecursor(int mCursor)
{
	int i;
	count++;
	move_count = count;
	move = mCursor;

	if (mCursor <= size1)
	{
		for (i=0; i < (size1 - mCursor); i++)
		{
			str2[size2 + i] = str1[size1 - i - 1];
			str1[size1 - i - 1] = '\0';
		}
		str2[size2 + i]  = '\0';

		size2 += (size1 - mCursor);
	}
	else
	{
		for ( i=0; i < (mCursor - size1); i++)
		{
			str1[size1 + i] = str2[size2 - i - 1];
			str2[size2 - i - 1] = '\0';
		}

		str1[size1 + i]  = '\0';
		size2 -= (mCursor - size1);
	}
	size1 = mCursor;
	printf ("Move) str1 [%s] size1 %d str2[%s] size2 %d\n", str1, size1,
			str2, size2);
}

void cmd_revert()
{
	int i;
	if (size2 == 0)
	{
		for (i=0; i < size1; i++)
			str2[i] = str1[size1 - i - 1];
		str2[i] = '\0';
		size2 = size1;
		size1 = 0;
		str1[0] = '\0';
		printf ("Revert 1) str1 [%s] size1 %d str2[%s] size2 %d\n", str1, size1, str2, size2);
		return;
	}

	if (size1 == 0)
	{
		for (i=0; i < size2; i++)
			str1[i] = str2[size2 - i - 1];
		str1[i] = '\0';
		size1 = size2;
		size2 = 0;
		str2[0] = '\0';
		printf ("Revert 2) str1 [%s] size1 %d str2[%s] size2 %d\n", str1, size1, str2, size2);
		return;
	}

	if (move_count > input_count)
	{
		if (move)
		{
			cmd_movecursor (size1 + move);
			move = 0;
		}

		if (input_size)
		{
			str1[size1 - input_size] = '\0';
			size1 -= input_size;
			input_size = 0;
			printf ("Revert 3) str1 [%s] size1 %d str2[%s] size2 %d\n", str1, size1, str2, size2);
			return;
		}
		else
		{
			input_size = my_strlen(input);
			int i;
			for ( i=0; i < input_size; i++)
				str1[size1 + i] = input[i];
			str1[size1 + i]  = '\0';
			size1 += input_size;
			printf ("Revert 4) str1 [%s] size1 %d str2[%s] size2 %d\n", str1, size1, str2, size2);
			return;
		}
	}
	else
	{
		if (move)
		{
			size1 = move;
			str1[size1] = '\0';
			move = 0;
			input_size = 0;
			printf ("Revert + Move) str1 [%s] size1 %d str2[%s] size2 %d\n", str1, size1, str2, size2);
		}
	}
}

void get_substring(int mPosition, int mLength, char res[])
{
	if (mPosition <= size1)
	{
		if ((mPosition + mLength) <= size1)
		{
			int  i;
			for (i = 0; i < mLength; i++)
				res[i] = str1[mPosition + i];
			res[i] = '\0';
			printf ("output [%s]\n", res);
			return;
		}

		int i, ii;
		for ( i = 0; i < (size1 - mPosition); i++)
			res[i] = str1[mPosition + i];
		for (ii = 0; ii < (mPosition + mLength - size1); ii++)
			res[i + ii] = str2[size2 - ii - 1];

		res[i + ii] = '\0';
		printf ("output [%s]\n", res);
		return;
	}

	int i;
	for (i = 0; i < mLength; i++)
		res[i] = str2[mPosition - size1 + i - 1];
	res[i] = '\0';
	printf ("output [%s]\n", res);
	return;
}
