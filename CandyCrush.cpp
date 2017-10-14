#include <stdio.h>
#include <stdlib.h>
#define ROW 10
#define COL 10
#define MAX 6

static int grid[ROW][COL];
int visited[ROW][COL];

int c_height[COL];

void dump()
{
	static int var = 0;
	printf ("========%d========\n", var++);
	for(int x=0;x<ROW;x++)
	{
		for(int y=0;y<COL;y++)
			printf ("%d", grid[x][y]);
		printf ("\n");
	}
}

int count()
{
	int c = 0;
	int tmp = 0;
	for(int x=0;x<ROW;x++)
		for(int y=0;y<COL;y++)
			if (grid[x][y])
				c++;

	for(int y=0;y<COL;y++)
		tmp += c_height[y];

	if (tmp != c)
		printf ("ERROR \n");

	return c;
}

void up_down(int xx, int yy)
{
	int type = grid [xx][yy];
	int count = 0;

	int x = xx;
	int y = yy;

	//UP
	x = xx; y = yy;
	while (1)
	{
		if ((x-1) < 0 || grid[x-1][y] != type)
			break;
		count++;
		x = x - 1;
	};

	//DOWN
	x = xx; y = yy;
	while (1)
	{
		if ((x+1) >= ROW || grid[x+1][y] != type)
			break;
		count++;
		x = x + 1;
	}

	if (count > 2)
	{
		//set in visited
		x = xx; y = yy;
		while (1)
		{
			if ((x-1) < 0 || grid[x-1][y] != type)
				break;
			visited[x-1][y] = 1;
			x = x - 1;
		};

		//DOWN
		x = xx; y = yy;
		while (1)
		{
			if ((x+1) >= ROW || grid[x+1][y] != type)
				break;
			visited[x+1][y] = 1;
			x = x + 1;
		}
		visited[xx][yy]=1;
	}
}

void left_right(int xx, int yy)
{
	int type = grid [xx][yy];
	int count = 0;

	int x = xx;
	int y = yy;

	//LEFT
	x = xx; y = yy;
	while (1)
	{
		if ((y-1) < 0 || grid[x][y-1] != type)
			break;
		count++;
		y = y - 1;
	};

	//RIGHT
	x = xx; y = yy;
	while (1)
	{
		if ((y+1) >= COL || grid[x][y+1] != type)
			break;
		count++;
		y = y + 1;
	}

	if (count >= 2)
	{
		//set in visited
		x = xx; y = yy;
		while (1)
		{
			if ((y-1) < 0 || grid[x][y-1] != type)
				break;
			visited[x][y-1] = 1;
			y = y - 1;
		};

		//RIGHT
		x = xx; y = yy;
		while (1)
		{
			if ((y+1) >= ROW || grid[x][y+1] != type)
				break;
			visited[x][y+1] = 1;
			y = y + 1;
		}
		visited[xx][yy]=1;
	}
}

void diagnol1(const int xx, const int yy, int flag)
{
	int type = grid [xx][yy];
	int count = 0;

	int x = xx;
	int y = yy;

	//UPPER LEFT
	x = xx; y = yy;
	while (1)
	{
		if ((x-1) < 0 || (y-1) < 0 || grid[x-1][y-1] != type)
			break;

		if (flag == 0)
			count++;
		else
			visited[x-1][y-1] = 1;
		y = y - 1;
		x = x - 1;
	};

	//DOWN RIGHT
	x = xx; y = yy;
	while (1)
	{
		if ((x+1) >= ROW || (y+1) >= COL || grid[x+1][y+1] != type)
			break;

		if (flag == 0)
			count++;
		else
			visited[x+1][y+1] = 1;
		y = y + 1;
		x = x + 1;
	}

	if (count >= 2)
	{
		diagnol1(xx, yy, 1);
		visited[xx][yy]=1;
	}
}

void diagnol2(const int xx, const int yy, int flag)
{
	int type = grid [xx][yy];
	int count = 0;

	int x = xx;
	int y = yy;

	//UPPER RIGHT
	x = xx; y = yy;
	while (1)
	{
		if ((x-1) < 0 || (y+1) < 0 || grid[x-1][y+1] != type)
			break;

		if (flag == 0)
			count++;
		else
			visited[x-1][y+1] = 1;
		y = y + 1;
		x = x - 1;
	};

	//DOWN LEFT
	x = xx; y = yy;
	while (1)
	{
		if ((x+1) >= ROW || (y-1) >= COL || grid[x+1][y-1] != type)
			break;

		if (flag == 0)
			count++;
		else
			visited[x+1][y-1] = 1;
		y = y - 1;
		x = x + 1;
	}

	if (count >= 2)
	{
		diagnol2(xx, yy, 1);
		visited[xx][yy]=1;
	}
}


int delete_elements()
{
	int flag = 0;
	for (int i = 0; i < COL; i++)
	{
		int height = c_height[i];
		for (int j = ROW - height; j < ROW; j++)
		{
			if (visited[j][i])
			{
				flag = 1;

				//shift elements down from ROW-height till j index
				for (int k=j; k > ROW-height; k--)
					grid[k][i] = grid[k-1][i];

				grid[ROW-height][i] = 0;
				height--;
				visited[j][i] = 0;
			}
			c_height[i] = height;
		}
	}
	return flag;
}

void blast ()
{
	int type;

reset:
	for (int i = 0; i < COL; i++)
	{
		int height = c_height[i];
		for (int j = ROW - height; j < ROW; j++)
		{
			type = grid[j][i];
			if (type)
			{
				up_down(j, i);
				left_right(j, i);
				diagnol1(j, i, 0);
				diagnol2(j, i, 0);
			}
		}
	}	
	if (delete_elements())
	{
		dump();
		goto reset;
	}
}


int land(int g[ROW][COL])
{
	for (int i=0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
			grid[i][j] = g[i][j];
		c_height[i]=ROW;
	}

	dump();
	blast();
	dump();
	return count();
}
