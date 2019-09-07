/*
 * Job.h
 *
 *  Created on: Sep 7, 2019
 *      Author: alex
 */

#ifndef JOB_H_
#define JOB_H_

class Job {
private:
	int startTime;
	int endTime;
	int value;
public:
	Job();
	Job(int start, int end, int weight);
	bool operator< (Job rhs) const;
	bool operator> (Job rhs) const;

	//bool compStrict(Job lhs, Job rhs);

	int getValue();
	int getEnd();
	int getStart();
};

#endif /* JOB_H_ */
