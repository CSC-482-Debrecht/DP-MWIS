/*
 * QuickSort.h
 *
 *  Created on: Jul 22, 2019
 *      Author: alex
 */

#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include "ArrayOperations.h"

template <typename E>
int partition(E array[], int lowerBound, int upperBound, E& pivot) {
	do {
		while (array[++lowerBound] < pivot);
		while (lowerBound < upperBound && pivot < array[--upperBound]);
		swap(array, lowerBound, upperBound);
	} while (lowerBound < upperBound);
	return lowerBound;
}

template <typename E>
int findPivot(E array[], int lowerBound, int upperBound) {
	return (upperBound + lowerBound)/2;
}

template <typename E>
void QuickSort(E array[], int lowerBound, int upperBound) {
	if (upperBound <= lowerBound) return;

	// Find pivot
	int pivotIndex = findPivot<E>(array, lowerBound, upperBound);
	// Move pivot to end to calculate partitioning of array
	swap(array, pivotIndex, upperBound);

	// Partition array
	int rightStart = partition<E>(array, lowerBound - 1, upperBound, array[upperBound]);
	// Replace pivot at correct location
	swap(array, rightStart, upperBound);
	// Sort subarrays, excluding pivot location
	QuickSort<E>(array, lowerBound, rightStart - 1);
	QuickSort<E>(array, rightStart + 1, upperBound);
}

#endif /* QUICKSORT_H_ */
