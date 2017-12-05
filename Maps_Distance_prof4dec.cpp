#include <stdio.h>
#define MAX 52
#define MAX_BUILDING 1001

#define BUILDING 1
#define INTERSECTION 2
#define PARKING 3

enum 
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
	MAX_DIRECTIONS
};

typedef struct
{
	int id;
	int locx, locy;
	int w, h;
	int px, py;
}Node;

int map [MAX][MAX];
int N;

Node node[MAX_BUILDING];

int g_id;
int cnt;
typedef struct
{
	int x, y;
	int dir;
	int steps;
}BFS;

BFS bfsnode [MAX*MAX*MAX_DIRECTIONS];

void init(int n)
{
	g_id = 0;
	cnt=0;
	N=n+2;
	for (int i=0; i < N; i++)
		for (int j=0; j < N; j++)
			map[i][j] = 0;
}

void addBuilding(int id, int locX, int locY, int  w, int h, int px, int py)
{
	g_id++;
	printf ("ADD %d: x %d y %d w %d h %d px %d py %d\n", id, locX, locY, w, h, px, py);
	node[id].locx = locX;
	node[id].locy = locY;
	node[id].w = w;
	node[id].h = h;
	node[id].px = locX + px;
	node[id].py = locY + py;
	

	for (int i=0; i < h; i++)
		for (int j=0; j < w; j++)
			map[locX + i] [locY + j] = id;//BUILDING;


	map[locX + px][locY + py] = PARKING;

	map[locX - 1][locY - 1] = INTERSECTION;
	map[locX - 1][locY + w] = INTERSECTION;
	map[locX + h][locY - 1] = INTERSECTION;
	map[locX + h][locY + w] = INTERSECTION;
}


int issafe (int x, int y)
{
	if (x < 0 || x > N || y < 0 || y > N || map[x][y] == BUILDING || map[x][y] == PARKING)
		return 0;
	return 1;
}

int isclockwise (int x, int y, int dir)
{
	switch (dir)
	{
		case UP:
			if (map[x][y + 1] == 1)
				return 1;
			return 0;
			break;
		case DOWN:
			if (map[x][y - 1] == 1)
				return 1;
			return 0;
			break;
		case LEFT:
			if (map[x - 1][y] == 1)
				return 1;
			return 0;
			break;
		case RIGHT:
			if (map[x + 1][y] == 1)
				return 1;
			return 0;
			break;
		default:
			return 0;
	}
	return 0;
}

void enqueue(int x, int y, int dir, int steps, int visited [MAX][MAX][MAX_DIRECTIONS])
{
	if (!visited[x][y][dir])
	{
		bfsnode[cnt].x = x;
		bfsnode[cnt].y = y;
		bfsnode[cnt].dir = dir;
		bfsnode[cnt].steps = steps + 1;
		visited[x][y][dir] = 1;
		cnt++;
	}
}

void dumpmap()
{
	for (int i=0; i < N; i++)
	{
		for (int j=0; j < N; j++)
			printf ("%d", map[i][j]);
		printf ("\n");
	}

	for (int i=1; i <= g_id; i++)
	{
		printf ("%d: x %d y %d w %d h %d \n", node[i].id, node[i].locx, node[i].locy, node[i].w, node[i].h);
	}
}



int getDistance(int from, int to)
{
	int x, y, dir, steps;
	int visited[MAX][MAX][MAX_DIRECTIONS];
	cnt = 0;

	dumpmap();
	//Enqueue 4 Directions
	{
		enqueue ( node[from].px, node[from].py + 1, RIGHT, 0, visited);
		enqueue ( node[from].px, node[from].py - 1, LEFT, 0, visited);
		enqueue ( node[from].px - 1, node[from].py, UP, 0, visited);
		enqueue ( node[from].px + 1, node[from].py, DOWN, 0, visited);
	}


	int i = -1;
	while (i < cnt)
	{
		i++;
		x = bfsnode[i].x;
		y = bfsnode[i].y;
		dir = bfsnode[i].dir;
		steps = bfsnode[i].steps;

		if (issafe (x, y) == 0)	
			continue;

		if (isclockwise (x, y, dir) == 0)
			continue;

		if (map[x][y] == INTERSECTION)
		{
			//Enqueue 4 Directions
			enqueue ( x, y + 1, RIGHT, steps, visited);
			enqueue ( x, y - 1, LEFT, steps, visited);
			enqueue ( x - 1, y, UP, steps, visited);
			enqueue ( x + 1, y, DOWN, steps, visited);
		}
		else
		{
			//enqueue respective direction
			switch (dir)
			{
				case RIGHT:
				case DOWN:
					enqueue ( x, y + 1, RIGHT, steps, visited);
					enqueue ( x + 1, y, DOWN, steps, visited);
					break;
				case LEFT:
				case UP:
					enqueue ( x, y - 1, LEFT, steps, visited);
					enqueue ( x - 1, y, UP, steps, visited);
					break;
			}
		}

		if (bfsnode[i].x == node[to].px && bfsnode[i].y == node[to].py)
			return bfsnode[i].steps;
	}


	return 0;
}
