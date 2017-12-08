#include <stdio.h>

#define MAX 10

int arr[MAX] = {10,9,1,2,6,5,4,7,8,3};


#define MAXSZ  (2 << 10)

int heap[MAXSZ];

int heapsz = 0;


void insert (int x)
{
	int i = heapsz;
	heapsz++;
	heap[i] = x;

	while (i != 0 && heap[i] > heap[ (i - 1)/2])
	{
		int tmp = heap[i];
		heap[i] = heap[(i - 1)/2];
		heap[(i - 1)/2] = tmp;

		i = (i - 1)/2;
	}
}

void maxheapify (int index)
{
	int max = index;

	int l = 2 * index + 1;
	int r = 2 * index + 2;

	if (l < heapsz && heap[max] < heap[l])
		max = l;
	if (r < heapsz && heap[max] < heap[r])
		max = r;

	if (max != index)
	{
		int tmp = heap[max];
		heap[max] = heap[index];
		heap[index] = tmp;
		maxheapify (max);
	}
}

void mydelete()
{
	heap[0] = heap[heapsz];
	heapsz--;
	maxheapify (0);
}

int main()
{
	for (int i=0; i < MAX; i++)
	{
		printf ("%d ", arr[i]);

		insert(arr[i]);
	}

	printf ("\n");
	for (int i = 0; i < MAX; i++)
	{
		printf ("%d ", heap[0]);
		mydelete ();
	}
	printf ("\n");
	return 0;
}

