#pragma once

#include <chrono>
#include <string>
#include <ctime>
#include <sstream>
#include <map>


class InsituTimer
{
	std::map< std::string, std::chrono::time_point<std::chrono::system_clock> > timers;		
	std::map< std::string, std::chrono::duration<double> > timers_duration;

  public:
	InsituTimer(){};
	InsituTimer(std::string timerName){ start(timerName); }
	~InsituTimer(){};

	int start(std::string timerName);
	int stop(std::string timerName);

	double getCurrentDuration(std::string timerName);	// time in seconds since timer started
	double getDuration(std::string timerName);		    // time in seconds

	static std::string getCurrentTime();	// get the current time
};



inline int InsituTimer::start(std::string timerName) 
{ 
	auto startTime = std::chrono::system_clock::now();
	if (timers.find(timerName) == timers.end())
		timers.insert( std::pair<std::string,std::chrono::time_point<std::chrono::system_clock>>(timerName,startTime) );	
	else
	{
		timers[timerName] = startTime;

		// remove previous durarion
		auto it=timers_duration.find(timerName);
		if (it !=timers_duration.end())
  			timers_duration.erase(it); 
	}

	return 1;
}


inline int InsituTimer::stop(std::string timerName) 
{ 
	if (timers.find(timerName) != timers.end())
	{
		auto endTime = std::chrono::system_clock::now(); 
		auto elapsed_time = endTime - timers[timerName];

		//auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed_time).count();
		timers_duration.insert( std::pair<std::string,std::chrono::duration<double>>(timerName, elapsed_time) );
		return 1;
	}
	else
	{
		std::cout << "Timer " << timerName << " does NOT exist!!!" << std::endl;
		return -1;
	}
}


inline double InsituTimer::getDuration(std::string timerName) 
{ 
	if (timers_duration.find(timerName) != timers_duration.end())
	{
		return (timers_duration[timerName]).count(); 
	}
	else
	{
		std::cout << "Timer " << timerName << " does NOT exist!!!" << std::endl;
		return -1;
	}
}