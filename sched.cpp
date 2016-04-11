#include <iostream>
#include <iomanip>
#include <string>
#include "sched.h"

using namespace std;

/*************************
** File: sched.cpp
** Project: CMSC 202 Project 1, Spring 2016
** Author: Matthew Grant
** Date: 2/23/16
** Section: 14
** E-Mail: mgr1@umbc.edu
*************************/




// FUNCTION PROTOTYPES -- DO NOT CHANGE!

// sort() - sorts an array of floats returning sorted indices
// On return, indx[] is an array of indices such that data[indx[0]], 
// data[indx[1]], ..., data[indx[len-1]] is data[] in ascending order.
//
// Parameters
//    data[] - float array of data to be ordered
//    indx[] - int array, same length as data[], to hold indices
//    len - int specifying the length of data[] and indx[]

void sort(float data[], int indx[], int len);

// sched() - schedules events given start and end times, and indx[] from sort
// Returns number of events scheduled; on return, scheduled[] contains 
// indices of scheduled events (e.g. startTime[scheduled[0]] is the start
// time of the first schedled event).
//
// Parameters
//    startTime[] - float array of event start times
//    endTime[] - float array of event end times
//    indx[] - array of indices that orders the end times
//    scheduled[] - int array to hold indices of scheduled events
//    len - int specifying the length of the arrays
// Returns
//    int value specifying number of events scheduled

int sched(float startTime[], float endTime[], int indx[], int scheduled[], int len);

// printEvent() - prints an event to the console
// Converts float start and end times to hh:mm format and prints times
// along with description.  E.g. Study Session from 12.5 to 13.25 should
// print as "12:30 - 13:15 Study Session"
//
// Parameters
//    startTime - float event start time
//    endTime - float event end time
//    description - string event description

void printEvent(float startTime, float endTime, string description);

// MAIN PROGRAM - DO NOT CHANGE!

int main() {

  int indx[NUM_EVENTS];
  int scheduledEvents[NUM_EVENTS];
  int numSched;

  // Sort by event ending times
  sort(endTime, indx, NUM_EVENTS);
  
  // Call greedy scheduling algorithm
  numSched = sched(startTime, endTime, indx, scheduledEvents, NUM_EVENTS);

  // Display scheduled events
  for (int i = 0; i < numSched; i++)
    printEvent(startTime[scheduledEvents[i]], endTime[scheduledEvents[i]],
	       description[scheduledEvents[i]]);

  return 0;
}

//
// FUNCTION IMPLEMENTATIONS GO HERE
//  


void sort(float data[], int indx[], int len){
  // Sorts the events in ascending order of end time
  // Loop through the list of endtimes, and record the index
  // of each endtime in ascending order

  // Populate indx with indices from 0 to len-1  
  
  for (int i = 0; i < len; i++){
    indx[i] = i;
  }


  /* Sort the indices by comparing values in the data list
     and switching them according to their value*/

  int currentMin;

  for (int j = 0; j < len; j++){

    for (int k = 0; k < len; k++){

      if (data[indx[j]] < data[indx[k]]){
	
	currentMin = indx[j];

	indx[j] = indx[k];

	indx[k] = currentMin;

      }
    }
  }
  
}

int sched(float startTime[], float endTime[], int indx[], int scheduled[], int len){

  /* Runs a "greedy" scheduling algorithm
     based on start and end time. Populates
     a list of indices of the scheduled events,
     but returns the number of scheduled events.
  */

  // Schedule the first event on the indx list

  scheduled[0] = indx[0];

  int numSched = 1;

  int prevAdd = 0;

  /* Schedule only events which do not start before the end time
     of the first event*/
  for (int i=1; i<len; i++){

      if (startTime[indx[i]] >= endTime[indx[prevAdd]]){

	scheduled[numSched] = indx[i];

	prevAdd = i;

	numSched++;
      }
    }

  return numSched;
}


void printEvent(float startTime, float endTime, string description){

  // Formats the given numbers so that they will print with the proper formatting

  // Get the starting hours and starting minutes

  int startHour = startTime / 1;

  int startMin = 60*(startTime - startHour);

  int endHour = endTime / 1;

  int endMin = 60*(endTime - endHour);

  // use setFill and setw to ensure that times are printed in a correct and easy-to-read way

  cout << setfill('0') << setw(2) << startHour << ':' << setfill('0') << setw(2)
       << startMin << " - " << setfill('0') << setw(2) << endHour << ':' << setfill('0') << setw(2) << endMin << ' ' << description << endl;

}
