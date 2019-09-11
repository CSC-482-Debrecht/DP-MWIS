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
using std::max; using std::cout; using std::max;

// A few globals, for ease of reference in main
const int NUM_EVENTS = 12;
int OPT[NUM_EVENTS + 1][NUM_EVENTS + 1];
std::set<int> selectedEventsP1[NUM_EVENTS+1][NUM_EVENTS+1];
std::set<int> selectedEventsP2[NUM_EVENTS+1][NUM_EVENTS+1];

// Determine latest possible non-conflicting event for each event l
void CalcConflicts(Job jobs[], int c[], int size) {
	// Get start and end times for each job
	c[0] = 0;
	int endTimes[size];
	int startTimes[size];
	for (int i = 0; i < size; ++i) {
		endTimes[i] = jobs[i].getEnd();
		startTimes[i] = jobs[i].getStart();
	}

	// Vectorize for use with upper_bound
	std::vector<int> vec(endTimes, endTimes + size);

	// Get c(l) for all l
	// Find first end time > start time l. Previous event is last earlier non-conflicting event.
	std::vector<int>::iterator upper;
	for (int l = 1; l < size; ++l) {
		upper = std::upper_bound(vec.begin(), vec.end(), startTimes[l]);
		c[l] = upper - vec.begin() - 1;
	}
}

// Determine value of optimal solution
void CalcOptimal(Job events[], int c[], const int NUM_EVENTS) {
	// Sum(v_1..v_n) must be less than INF
	const int INF = 1<<16;

	// Base case -- when no one goes to anything, value is 0
	OPT[0][0] = 0;

	// Also sets an auxiliary array that keeps track of the event combinations chosen for each optimal solution
	// Loop over all possible combinations of j and k
	for (int j = 0; j < NUM_EVENTS + 1; ++j) {
		for (int k = j; k < NUM_EVENTS + 1; ++k) {
			// If they're equal, this option is impossible
			if (j == k) {
				if (j != 0)	OPT[j][k] = -INF; // (protect base case)
			// If they're not equal, then we can set both OPT[j][k] and OPT[k][j] in the same step (symmetric under exchange of people)
			} else {
				// Reset curMax each time
				int curMax = 0;
				// Loop through all events guaranteed not to conflict with an earlier choice
				for (int l = 0; l <= c[k]; ++l) {
					if (OPT[j][l] > curMax) {
						curMax = OPT[j][l];
						selectedEventsP1[j][k].clear();
						selectedEventsP2[j][k].clear();
						selectedEventsP1[k][j].clear();
						selectedEventsP2[k][j].clear();
						selectedEventsP1[j][k] = selectedEventsP1[j][l];
						selectedEventsP2[j][k] = selectedEventsP2[j][l];
						selectedEventsP1[k][j] = selectedEventsP1[l][j];
						selectedEventsP2[k][j] = selectedEventsP2[l][j];
					}
					// If you didn't want to keep track of chosen events, you could use a max instead of an if
					//curMax = max(curMax, OPT[j][l]);
				}
				// Add value of event k
				OPT[j][k] = OPT[k][j] = events[k].getValue() + curMax;
				// Add event k to solution set
				// Note that event j is already present in appropriate solution set, so need not be added here
				selectedEventsP2[j][k].insert(k);
				selectedEventsP1[k][j].insert(k);
			}
		}
	}
}

int main() {
	int c[NUM_EVENTS];
	memset(OPT, 0, sizeof(OPT));

	// Set up test problem
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

	// Sort by end time (and weight, though that's not required)
	QuickSort<Job>(events, 0, NUM_EVENTS);

	// Calculate the latest possible prior non-conflicting event
	CalcConflicts(events, c, NUM_EVENTS + 1);

	// Calculate optimal solution for all possible combinations
	CalcOptimal(events, c, NUM_EVENTS);

	int lastEvent = NUM_EVENTS;
	// Determine maximum value of solution for all events
	int maxPoss = 0;
	int finalEvents[2];
	for (int j = 1; j <= lastEvent; ++j) {
		for (int k = 1; k <= lastEvent; ++k) {
			if (OPT[j][k] > maxPoss) {
				maxPoss = OPT[j][k];
				finalEvents[0] = j;
				finalEvents[1] = k;
			}
		}
	}

	// Display solution
	cout << "Events selected by person 1: ";
	for (int const &event: selectedEventsP1[finalEvents[0]][finalEvents[1]]) {
		cout << event << " ";
	}
	cout << "\nEvents selected by person 2: ";
	for (int const &event: selectedEventsP2[finalEvents[0]][finalEvents[1]]) {
			cout << event << " ";
		}
}
