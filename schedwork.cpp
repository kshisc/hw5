#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
	const AvailabilityMatrix& avail,
	const size_t dailyNeed,
	const size_t maxShifts,
  DailySchedule& sched,
	size_t row, size_t col,
	map<size_t,size_t>& shiftMap);

// Implementation
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched)
{
	if(avail.size()==0U){ //empty
		return false;
	}
	sched.clear(); //reset

	size_t n = avail.size(); //rows=days
	sched.resize(n,vector<Worker_T>()); //n by d matrix
	map<size_t,size_t> shiftMap; //tracks each worker's shifts
	return scheduleHelper(avail,dailyNeed,maxShifts,sched,0,0,shiftMap);
}

bool scheduleHelper(
	const AvailabilityMatrix& avail,
	const size_t dailyNeed,
	const size_t maxShifts,
  DailySchedule& sched,
	size_t row, size_t col,
	map<size_t,size_t>& shiftMap)
{
	if(row==avail.size()){ //all days are scheduled
		return true;
	}

	if(sched[row].size()!=dailyNeed){ //more workers needed
		while(col<avail[0].size()){
			if(avail[row][col]==1){ //worker available
				if(shiftMap[col]<maxShifts){ //maxShifts not reached
					sched[row].push_back(col); //schedule worker
					shiftMap[col]++;

					bool check = scheduleHelper(avail,dailyNeed,maxShifts,sched,row,col+1,shiftMap);
					if(check){ //done
						return true;
					}
					else{ //backtrack
						sched[row].pop_back();
						shiftMap[col]--;
					}
				}
			} 

			col++; //next worker
		}
	}
	
	else{
		//next day
		return scheduleHelper(avail,dailyNeed,maxShifts,sched,row+1,0,shiftMap);
	}

	return false;
}