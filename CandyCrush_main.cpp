
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define ROW 10
#define COL 10
#define MAX 6

int x,y;
static int grid[ROW][COL];
void initialize();

static void dump()
{
	for(x=0;x<ROW;x++)
	{
		for(y=0;y<COL;y++)
		{
			printf ("%d", grid[x][y]);
		}
		printf ("\n");
	}
}


extern int land(int arr[ROW][COL]);

int main()
{
	printf("-------NUMBER CRUSH-------\n***************************\n\n");
	//while(1)
	{
		printf("-------NUMBER CRUSH-------\n***************************\n\n");
		initialize();
		dump();
		int ret = land(grid);
		printf ("ret = %d\n", ret);
	}
	return 0;
}

/*define grid and populate with random numbers and print to screen*/
void initialize(void)
{
	int n;
//	srand(time(NULL));
	for(x=0;x<ROW;x++)
	{
		for(y=0;y<COL;y++)
		{
			n=(1+rand())%MAX;
			if (n == 0)
				n++;
			grid[x][y]=n;
		}
	}
}
