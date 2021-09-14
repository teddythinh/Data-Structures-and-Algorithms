#include <iostream>
using namespace std;

void bubbleSort(int* arr, int n)
{
	for (int i = 1; i <= n - 1; i++)
	{
		for (int j = n - 1; j >= i; j--)
		{
			if (arr[j] < arr[j - 1])
			{
				HoanVi(arr[j], arr[j - 1]);
			}
		}
	}
}

void heapify(int *arr, int n, int i)
{
	int largest = i;   
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i)
	{
		HoanVi(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}

void heapSort(int *arr, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	for (int i = n - 1; i > 0; i--)
	{
		HoanVi(arr[0], arr[i]);

		heapify(arr, i, 0);
	}
}

void insertionSort(int *arr, int n)
{
	int v, j;

	for (int i = 1; i < n; i++)
	{
		v = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > v)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = v;
	}
}

void selectionSort(int *arr, int n)
{
	int minidx, minval;
	for (int i = 0; i < n - 1; i++)
	{
		minidx = i;
		minval = arr[i];
		for (int j = i + 1; j < n; j++)
			if (arr[j] < minval)
			{
				minidx = j;
				minval = arr[j];
			}
		arr[minidx] = arr[i];
		arr[i] = minval;
	}
}

void binaryInsertionSort(int *arr, int n)
{
	int left, right, m, i;
	int x;

	for (int i = 1; i < n; i++)
	{
		x = arr[i];
		left = 0;
		right = i - 1;
		while (left <= right)
		{
			m = (left + right) / 2;
			if (x < arr[m])
				right = m - 1;
			else
				left = m + 1;
		}
		for (int j = i - 1; j >= left; j--)
			arr[j + 1] = arr[j];
		arr[left] = x;
	}
}

void quickSort(int *arr, int n, int left, int right)
{
	if (left < right)
	{
		int p = arr[left];
		int i = left;
		int j = right + 1;
		do
		{
			do
			{
				i++;
			} while (arr[i] < p);

			do
			{
				j--;
			} while (arr[j] > p);

			HoanVi(arr[i], arr[j]);
		} while (i < j);

		HoanVi(arr[i], arr[j]);
		HoanVi(arr[left], arr[j]);

		quickSort(arr, n, left, j - 1);
		quickSort(arr, n, j + 1, right);
	}
}

void merge(int *arr, int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	int *L = new int[n1];
	int *R = new int[n2];

	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	int i = 0;

	int j = 0;

	int k = l;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
	delete[] L;
	delete[] R;
}

void mergeSort(int *arr, int l, int r)
{
	if(l < r)		
	{
		int m = l + (r - 1) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

int getMax(int *arr, int n)
{
	int max = arr[0];
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}

void countingSort(int *arr, int size, int place)
{
	const int max = 10;
	int *output = new int[size];
	int count[max];

	for (int i = 0; i < max; i++)
	{
		count[i] = 0;
	}

	for (int i = 0; i < size; i++)
	{
		count[(arr[i] / place) % 10]++;
	}

	for (int i = 1; i < max; i++)
	{
		count[i] += count[i - 1];
	}

	for (int i = size - 1; i >= 0; i--)
	{
		output[count[(arr[i] / place) % 10] - 1] = arr[i];
		count[(arr[i] / place) % 10]--;
	}

	for (int i = 0; i < size; i++)
	{
		arr[i] = output[i];
	}
	delete[] output;
}

long long countCountingSort(int *arr, int n, int exp, long long &counting)
{
	int *output = new int[n];
	int i, count[10] = {0};

	for (i = 0; ++counting && i < n; i++)
		count[(arr[i] / exp) % 10]++;

	for (i = 1; ++counting && i < 10; i++)
		count[i] += count[i - 1];

	for (i = n - 1; ++counting && i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	for (i = 0; ++counting && i < n; i++)
		arr[i] = output[i];
	return counting;
}

void radixSort(int *arr, int size)
{
	int max = getMax(arr, size);

	for (int place = 1; max / place > 0; place *= 10)
	{
		countingSort(arr, size, place);
	}
}
