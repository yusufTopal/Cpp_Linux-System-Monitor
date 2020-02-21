#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    
    long time = seconds;
	long hour = 0;
	long min = 0;
	long sec = 0;
	string date;

	hour = time/3600;
	time = time%3600;
	min = time/60;
	time = time%60;
	sec = time;
    date = std::to_string(hour)+":"+std::to_string(min)+":"+std::to_string(sec);
    
    return date; }