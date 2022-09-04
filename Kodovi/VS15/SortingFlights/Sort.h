//============================================================================
// Name        : Sort.h
// Author      : Mihal Sabados
// Date        : 09.01.2021.
// Copyright   : 
// Description : Definition of Sort abstract class and its derived classes SelectionSort and MergeSort.
//============================================================================
#pragma once

#include "Flight.h"
#include <vector>


// Sort class
class Sort
{
protected:
	// number of comparisons performed in sort function
	unsigned long num_cmps;
	int iteration;
	int criteria;
public:
	// main entry point
	virtual void sort(std::vector<Flight>& data,int size) = 0;
	Sort(int it, int crit) :iteration(it), criteria(crit), num_cmps(0) {};
	// returns number of comparisons
	unsigned long getNumCmps();
	// resets the number of comparisons
	void resetNumCmps();
};

// SelectionSort class
class SelectionSort : public Sort
{
public:
	SelectionSort(int iteration, int criteria) :Sort(iteration, criteria) {};
	//sort vector of Flights with selection sort
	void sort(std::vector<Flight>& data,int size);
};

// MergeSort class
class MergeSort : public Sort
{
public:
	MergeSort(int iteration, int criteria) :Sort(iteration, criteria) {};
	//sort vector of Flights with merge sort
	void sort(std::vector<Flight>& data, int size);
	//splits vector in half and then sort them
	void mergeSort(std::vector<Flight>& data, int l, int r);
	//sort two halves of vector
	void merge(std::vector<Flight>& data, int left, int middle, int right);
};

