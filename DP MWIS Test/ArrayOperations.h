/*
 * ArrayOperations.h
 *
 *  Created on: Aug 13, 2019
 *      Author: alex
 */

#ifndef ARRAYOPERATIONS_H_
#define ARRAYOPERATIONS_H_

template <typename E>
inline void swap(E array[], int i, int j) {
	E temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

#endif /* ARRAYOPERATIONS_H_ */
