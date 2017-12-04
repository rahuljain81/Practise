/*
	Quick Sort implementation
	Idea is to select a pivot and all element on left of pivot will be small
	and all elements on right of pivot will be greater.
*/
#include <stdio.h>
#define MAX 10
int arr[MAX] = {1,2,3,4,5,6,7,8,9,10};

int partition (int low, int high)
{
	//Always highest element will be pivot
	int pivot = arr[high];

	//Select position which needs to be exchanged.
	int j = low - 1;
	
	for (int i=low; i < high; i++)
	{
		if (arr[i] > pivot)
		{
			//Needs SWAP
			//Increment position and exchange it with i position
			j++;
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}

	//Now, Incremented j is position where pivot element is to placed.
	//Left Side of J will be greater than pivot and Righ side will be greater
	j++;
	int tmp = arr[j];
	arr[j] = arr[high];
	arr[high]  = tmp;
	//Return Pivot Position
	return j;
}

void qs (int low, int high)
{
#if 0
	for (int i=0; i < MAX; i++)
		printf ("%d ", arr[i]);
	printf ("\n");
#endif
	//Only if low is less than high.
	if (low < high)
	{
		//Parition function is expected to return the pivot position.
		// L is pivot  and is at appropriate position. 
		// No need to inlcude it in next quick sort calls.
		int l = partition (low, high);
		//Run quicksort for left part less tan pivot
		qs (low, l - 1);
		//Run quicksort for right part greater than pivot
		qs (l + 1, high);
	}
}
int main()
{
	qs(0, MAX-1);
	for (int i=0; i < MAX; i++)
		printf ("%d ", arr[i]);
	printf ("\n");
	return 0;
}
