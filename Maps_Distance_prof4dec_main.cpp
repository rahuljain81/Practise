#include <iostream>
using namespace std;

static int Score = 0;

extern void init(int N);
extern void addBuilding(int id, int locX, int locY, int  w, int h, int px, int py);
extern int getDistance(int from, int to);

typedef enum
{
	CMD_INIT,
	CMD_ADD,
	CMD_GET,
	CMD_EXIT = 9
}COMMAND;

static void run()
{
	int N, cmd;
	int id, locX, locY, w, h, px, py;
	int from, to, dist, ret;
	cin >> cmd >> N;
	Score = 0;
	init(N);
	while (1)
	{
		cin >> cmd;
		if (cmd == CMD_ADD)
		{
			cin >> id >> locX >> locY >> w >> h >> px >> py;
			addBuilding(id, locX, locY, w, h, px, py);
		}
		else if (cmd == CMD_GET)
		{
			cin >> from >> to >> dist;
			ret = getDistance(from, to);
			if (ret == dist)
			{
				Score++;
			}
			else
			{
				printf ("Expected %d, Actual %d building (%d, %d)\n",dist, ret, from, to);
				break;
			}
		}
		else if (cmd == CMD_EXIT)
		{
			break;
		}
	}
}

int main()
{
	int T;
	cin >> T;
	int TotalScore = 0;
	for (int tc = 1; tc <= T; tc++)
	{
		run();
		TotalScore += Score;
		cout << "#" << tc << " " << Score << endl;
	}
	cout << "Total_Score=" << TotalScore << endl;

	return 0;
}
