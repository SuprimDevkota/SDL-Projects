#include "..\Headers\Header.h"

//Global Variables
SDL_Rect EmptyRect = { 0, 0, 0, 0 };
int speed = 10;	//change as per the number of bars, more bars = greater speed is ideal
int frames = 0;


//Array of Bar objects
LBar bar[NumberOfBars];

//Array of Bar heights for merge sort
int a[NumberOfBars], b[NumberOfBars];


void bubble_sort(int NumberOfBars)
{
	for (int i = 0; i < NumberOfBars - 1; i++)
	{
		for (int j = 0; j < NumberOfBars - i - 1; j++)
		{
			//Compare bars and get suitable clipping areas
			SDL_Rect* Clips = CompareBars(bar[j], bar[j + 1]);

			//Classic Bubble sort algorithm
			if (bar[j].bHeight > bar[j + 1].bHeight) {
				SwapBars(&bar[j], &bar[j + 1]);
			}
			else
			{
				//Reset the jth bar and j+1th back to original
				Revertbars(Clips[0], Clips[1]);
			}
		}
	}
}

void selection_sort(int NumberOfBars)
{
	int min_index;
	for (int i = 0; i < NumberOfBars; ++i)
	{
		min_index = i;
		for (int j = i; j < NumberOfBars; ++j)
		{
			SDL_Rect* Clips = CompareBars(bar[j], bar[min_index]);
			min_index = (bar[min_index].bHeight < bar[j].bHeight) ? min_index : j;
			Revertbars(Clips[0], Clips[1]);
		}

		SwapBars(&bar[i], &bar[min_index]);
	}
}

void insertion_sort(int NumberOfBars)
{
	for (int i = 1; i < NumberOfBars; ++i)
	{
		int current = bar[i].bHeight;
		int j = i - 1;

		while (bar[j].bHeight > current && j >= 0)
		{
			SDL_Rect* Clips = CompareBars(bar[j], bar[j + 1]);
			SwapBars(&bar[j], &bar[j + 1]);
			Revertbars(Clips[0], Clips[1]);
			j--;
		}
		bar[j + 1].bHeight = current;
	}
}

void merge(int l, int mid, int r)
{
	int n1 = mid - l + 1;
	int n2 = r - mid;

	for (int i = 0; i < n1; ++i)
	{
		a[i] = bar[l + i].bHeight;
	}

	for (int i = 0; i < n2; ++i)
	{
		b[i] = bar[mid + i + 1].bHeight;
	}

	int i = 0, j = 0, k = l; //k initialized to the low index of array

	while (i < n1 && j < n2)
	{
		if (a[i] < b[j])
		{
			SwapBars(&bar[k], NULL, a[i]);
			i++, k++;
		}
		else
		{
			SwapBars(&bar[k], NULL, b[j]);
			j++, k++;
		}
	}

	// if i pointer not till the end then copy it's remaining elements to the merged  array
	while (i < n1)
	{
		SwapBars(&bar[k], NULL, a[i]);
		i++, k++;
	}

	// if i pointer not till the end then copy it's remaining elements to the merged  array
	while (j < n2)
	{
		SwapBars(&bar[k], NULL, b[j]);
		j++, k++;
	}
}

void merge_sort(int l, int r)
{

	if (l < r)
	{
		int mid = (l + r) / 2;

		//break into two sections and recursive call
		merge_sort(l, mid);
		merge_sort(mid + 1, r);

		merge(l, mid, r);
	}
}

int partition(int l, int r)
{
	int pivot = bar[r].bHeight; //initialize pivot to last element

	//i -> element that is smallest to pivot. init -> less than starting index
	int i = l - 1;

	for (int j = l; j < r; ++j) //j init to the lowest index of array
	{
		if (bar[j].bHeight < pivot)
		{
			i++;
			SwapBars(&bar[i], &bar[j]);
		}
	}

	SDL_Rect* Clips = CompareBars(bar[i + 1], bar[r]);
	SwapBars(&bar[i + 1], &bar[r]); //i denotes the number that is least smallest to pivot
	Revertbars(Clips[0], Clips[1]);
	return i + 1;
}

void quick_sort(int l, int r)
{
	if (l < r)
	{
		int pi = partition(l, r); //returns partition index.
		quick_sort(l, pi - 1);    //sort before partition index.
		quick_sort(pi + 1, r);    //sort after partition index.
	}
}