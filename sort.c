#include "sort.h"






void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to perform Selection Sort
void sort(int** arr, int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {

        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j][1] < arr[min_idx][1])
                min_idx = j;

        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx][1], &arr[i][1]);
        swap(&arr[min_idx][0], &arr[i][0]);
    }
}
