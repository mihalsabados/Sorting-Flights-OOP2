//============================================================================
// Name        : Sort.cpp
// Author      : Mihal Sabados
// Date        : 09.01.2021.
// Copyright   : 
// Description : Implementation of the Sort class and his Derived classes SelectionSort and MergeSort.
//============================================================================

#include "Sort.h"

using namespace std;


void SelectionSort::sort(std::vector<Flight>& data, int size) {
    int i = iteration;
    int min_i = i;
    for (int j = i + 1; j < size; j++){
        if (data[min_i].compare(data[j], criteria) > 0) { min_i = j; }
        num_cmps++;
    }
	Flight temp = data[i];
	data[i] = data[min_i];
	data[min_i] = temp;
}

void MergeSort::sort(std::vector<Flight>& data, int size)
{
    mergeSort(data, 0, size - 1);
}


void MergeSort::mergeSort(std::vector<Flight>& data, int left, int right)
{
	if (left < right)
	{
		// Same as (l+r)/2 but avoids
		// overflow for large l & h
		int middle = left + (right - left) / 2;
		mergeSort(data, left, middle);
		mergeSort(data, middle + 1, right);
        if (iteration > 0) {
            merge(data, left, middle, right);
            iteration--;
        }
	}
}


void MergeSort::merge(std::vector<Flight>& data, int left, int middle, int right)
{
    int k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temp vectors
    vector<Flight> L, R;

    // Copy data to temp vector L and R
    for (int i = 0; i < n1; i++)
        L.push_back(data[left + i]);
    for (int j = 0; j < n2; j++)
        R.push_back(data[middle + 1 + j]);

    // Merge the temp vectors
    // back into data[l..r]
    int i = 0;
    int j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i].compare(R[j], criteria) <= 0)
        {
            data[k] = L[i];
            i++;
        }
        else
        {
            data[k] = R[j];
            j++;
        }
        num_cmps++;
        k++;
    }
    // Copy the remaining elements
    // of L, if there are any 
    while (i < n1)
    {
        data[k] = L[i];
        i++;
        k++;
    }
    // Copy the remaining elements
    // of R, if there are any 
    while (j < n2)
    {
        data[k] = R[j];
        j++;
        k++;
    }
}

unsigned long Sort::getNumCmps() {
	return num_cmps;
}

void Sort::resetNumCmps()
{
	num_cmps = 0;
}