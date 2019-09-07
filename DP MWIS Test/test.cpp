/*
 * test.cpp
 *
 *  Created on: Sep 7, 2019
 *      Author: alex
 */

#include "Job.h"
#include "QuickSort.h"
#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
using std::max; using std::cout; using std::min;

void CalcConflicts(Job jobs[], int c[], int size) {
	c[0] = 0;
	int endTimes[size];
	int startTimes[size];
	for (int i = 0; i < size; ++i) {
		endTimes[i] = jobs[i].getEnd();
		startTimes[i] = jobs[i].getStart();
	}

	std::vector<int> vec(endTimes, endTimes + size);

	std::vector<int>::iterator upper;
	for (int l = 1; l < size; ++l) {
		upper = std::upper_bound(vec.begin(), vec.end(), startTimes[l]);
		c[l] = upper - vec.begin() - 1;
	}
}

int CalcOptimal(Job events[], int c[], const int NUM_EVENTS) {
	int OPT[NUM_EVENTS + 1][NUM_EVENTS + 1][1<<NUM_EVENTS];
	memset(OPT, -1, sizeof(OPT));
	int option1, option2, option3, option4;
	for (int i = 0; i < 1<<NUM_EVENTS; ++i) {
		OPT[0][0][i] = 0;
	}
	for (int j = 0; j < NUM_EVENTS + 1; ++j) {
		for (int k = j; k < NUM_EVENTS + 1; ++k) {
			// mask is k bits long. The n-th bit is unset if event n has been used.
			for (int mask = (1 << k) - 1; mask >= 0; --mask) {
				// k > j
				if (j > 0) {
					option1 = OPT[j-1][k-1][mask >> 1];
					option2 = (OPT[j-1][c[k]][(mask &~ 1) >> min(k-(j-1), k-c[k])] + events[k].getValue())*(mask & 1U); // Check if we've used k yet
					option3 = (OPT[c[j]][k-1][(mask &~ (1UL << (k-j))) >> min(k-c[j], 1)] + events[j].getValue())*((mask >> (k-j)) & 1U); // Check if we've used j yet. The bit of interest is a distance k-j from the rightmost bit.
					// Can't take both j and k if they are equal
					if(j != k) {
						option4 = (OPT[c[j]][c[k]][(mask &~ (1UL << (j-1)) &~ (1UL << (k-1))) >> min(k-c[k], k-c[j])] + events[j].getValue() + events[k].getValue())*((mask >> (k-j)) & 1U)*(mask & 1U);
					} else {
						option4 = 0;
					}
				} else {
					option1 = 0;
					option2 = 0;
					option3 = OPT[0][k-1][mask >> 1];
					option4 = (OPT[0][c[k]][(mask &~ (1UL << (k-1))) >> (k-c[k])] + events[k].getValue())*(mask & 1U);
				}
				OPT[j][k][mask] = OPT[k][j][mask] = max(max(max(option1, option2),option3),option4);
			}
		}
	}

	return OPT[NUM_EVENTS][NUM_EVENTS][(1 << NUM_EVENTS)-1];
}

int main() {
	const int NUM_EVENTS = 12;
	int c[NUM_EVENTS];

	Job events[NUM_EVENTS+1];
	events[1] = Job(1,4,4);
	events[2] = Job(1,4,1);
	events[3] = Job(2,4,3);
	events[4] = Job(2,6,3);
	events[5] = Job(3,7,5);
	events[6] = Job(5,9,2);
	events[7] = Job(6,11,3);
	events[8] = Job(8,12,3);
	events[9] = Job(7,13,7);
	events[10] = Job(2,14,9);
	events[11] = Job(10,15,4);
	events[12] = Job(10,15,3);

	QuickSort<Job>(events, 0, NUM_EVENTS);

	//	for (int i = 0; i < NUM_EVENTS + 1; ++i) {
	//		cout << "Event: " << i << " Start: " << events[i].getStart() << " End: " << events[i].getEnd() << " Weight: " << events[i].getValue() << "\n";
	//	}

	CalcConflicts(events, c, NUM_EVENTS + 1);

	//	for (int i = 0; i < NUM_EVENTS + 1; ++i) {
	//		cout << "First event that does not conflict with event " << i << " is " << c[i] << "\n";
	//	}

	cout << CalcOptimal(events, c, NUM_EVENTS);

}
