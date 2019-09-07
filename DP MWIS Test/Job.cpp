/*
 * Job.cpp
 *
 *  Created on: Sep 7, 2019
 *      Author: alex
 */

#include "Job.h"

Job::Job() {
	startTime = 0;
	endTime = 0;
	value = 0;
}

Job::Job(int start, int end, int weight) {
	startTime = start;
	endTime = end;
	value = weight;
}

bool Job::operator<(Job rhs) const {
	if (this->endTime < rhs.endTime) return true;
	if (this->endTime == rhs.endTime && this->value < rhs.value) return true;
	return false;
}

bool Job::operator>(Job rhs) const {
	if (this->endTime > rhs.endTime) return true;
	if (this->endTime == rhs.endTime && this->value > rhs.value) return true;
	return false;
}

//bool Job::compStrict(Job lhs, Job rhs) {
//	if (lhs.endTime < rhs.endTime) return true;
//	return false;
//}

int Job::getValue() {
	return value;
}

int Job::getEnd() {
	return endTime;
}

int Job::getStart() {
	return startTime;
}
