#include <stdio.h>
#include <stdlib.h>
#define MAX_ACCOUNT 50000
#define MIN_ACCOUNT 10000
#define MAX_TIME 30000

#define MAX_STR 11

#define MAX_HASH	100000

typedef struct {
	char id[MAX_STR];
	int id_len;
	char password[MAX_STR];
	int password_len;
	int defaulttime;
	int loggedin;
	int expiretime;
}ACCOUNT;
static ACCOUNT account[MAX_ACCOUNT];

int account_cnt = 0;

int *arr[MAX_HASH];
int arr_cnt[MAX_HASH];

int *time[MAX_TIME];
int time_cnt[MAX_TIME];

int tick = 0;

int once = 0;
unsigned long hash (char id[MAX_STR])
{
	unsigned long hash = 5381;
	char c;

	while ((c = *id++))
		hash = ((hash << 5) + hash) + c;

	return hash%MAX_HASH;
}

void Init()
{
	account_cnt = 0;
	tick = 0;
	for (int i=0; i < MAX_HASH; i++)
		arr_cnt[i] = 0;
	for (int i=0; i < MAX_TIME; i++)
		time_cnt[i] = 0;

	if (once == 0)
	{
		for (int i=0; i < MAX_HASH; i++)
			arr[i] = (int *) malloc (sizeof (int) * MAX_ACCOUNT);
		for (int i=0; i < MAX_TIME; i++)
			time[i] = (int *) malloc (sizeof (int) * MAX_ACCOUNT);
		once = 1;
	}
}

int strcopy (char *src, char *dest)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i++] = '\0';
	return i;
}


int strcompare (char *first, char *second)
{
	int i = 0;
	while (first[i] != '\0' && second[i] != '\0' && first[i] == second[i])
		i++;

	if (first[i] == '\0' && second[i] == '\0')
		return 0;
	return 1;
}

void NewAccount(char id[MAX_STR], char password[MAX_STR], int defaulttime)
{

	account[account_cnt].id_len = strcopy (id, account[account_cnt].id);
	account[account_cnt].password_len = strcopy (password, account[account_cnt].password);
	account[account_cnt].defaulttime = defaulttime;
	account[account_cnt].loggedin = 1;

	unsigned long h = hash (account[account_cnt].id);
	arr[h][arr_cnt[h]] = account_cnt;
	arr_cnt[h]++;

	int expire = tick + account[account_cnt].defaulttime - 1;
	time[expire][time_cnt[expire]] = account_cnt;
	time_cnt[expire]++;

	account[account_cnt].expiretime = expire;

	printf ("%d: id %s passwd %s time %d expire %d\n", account_cnt, account[account_cnt].id, account[account_cnt].password, account[account_cnt].defaulttime, expire);

	account_cnt++;
}

void Logout(char id[MAX_STR])
{
	printf ("LoggedOut Request for id %s\n", id);
	unsigned long h = hash (id);

	int len = arr_cnt[h];

	for (int i = 0; i < len; i++)
	{
		int acc = arr[h][i];

		if (strcompare (account[acc].id, id) == 0)
		{
			account[acc].loggedin = 0;
			printf ("LoggedOut %d\n", acc);
		}
	}
}

void Connect(char id[MAX_STR], char password[MAX_STR])
{
	printf ("Connect Request for id %s password %s\n", id, password);
	unsigned long h = hash (id);

	int len = arr_cnt[h];

	for (int i = 0; i < len; i++)
	{
		int acc = arr[h][i];

		if (strcompare (account[acc].id, id) == 0 && strcompare (account[acc].password, password) == 0 && account[acc].loggedin)
		{
			account[acc].loggedin = 1;
			int expire = tick + account[acc].defaulttime - 1;

			if (expire > MAX_TIME)
			{
				printf ("EXPIRE TIME %d is more than MAX_TIME %d\n", expire, MAX_TIME);
				continue;
			}

			time[expire][time_cnt[expire]] = acc;
			time_cnt[expire]++;
			account[acc].expiretime = expire;
			printf ("LoggedIn %d expire %d\n", acc, expire);
		}
	}
}

int Tick()
{

	printf ("Tick %d\n", tick);

	int a = 0;

	for (int i=0; i < time_cnt[tick]; i++)
	{
		int acc = time[tick][i];

		if (account[acc].loggedin && account[acc].expiretime == tick)
		{
			printf ("Tick acc %d\n", acc);
			a++;
			account[acc].loggedin = 0;
		}
	}
	tick++;
	return a;
}
