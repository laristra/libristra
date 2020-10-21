#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

extern std::stringstream debugLog;
extern std::string debugLogName;

class InsituLog
{
	std::string outputFilename;

  public:
	std::stringstream log;

	InsituLog(){ outputFilename = "untitled.log"; }
	InsituLog(std::string _outputFilename): outputFilename(_outputFilename){ }
	~InsituLog();

	void setOutputFilename(std::string _outputFilename){ outputFilename = _outputFilename; }
	void clear(){ log.str(""); }
	void writeToDisk();
};


inline InsituLog::~InsituLog()
{
	outputFilename = "";
	log.str("");
}


inline void InsituLog::writeToDisk()
{
	std::ofstream outputFile( outputFilename.c_str(), std::ios::out);
	outputFile << log.str();
	outputFile.close();
}



///////////////////////////////////////////////////////////////////////////////////
///////////// Simple Logging

inline void writeLog(std::string filename, std::string log)
{
	std::ofstream outputFile( (filename+ ".log").c_str(), std::ios::out);
	outputFile << log;
	outputFile.close();
}

inline void writeLogApp(std::string filename, std::string log)
{
	std::ofstream outputFile( (filename+ ".log").c_str(), std::ios::out | std::ios::app);
	outputFile << log;
	outputFile.close();
}

inline void writeLogNew(std::string filename, std::string log)
{
	std::ofstream outputFile( (filename+ ".log").c_str(), std::ios::out);
	outputFile << log;
	outputFile.close();
}