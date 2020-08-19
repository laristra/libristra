#pragma once

#include <vector>
#include <string>

#include "json.hpp"

inline std::vector<std::string> getCatalystScripts(std::string inputFilename)
{
	std::vector<std::string> catalyst_scripts;
    if (inputFilename != "")
    { 
      //
      // Find the path 
      std::size_t foundBackslash = inputFilename.find_last_of("/");
      std::string catalystPath = inputFilename.substr(0,foundBackslash);

      //
      // Pass JSON file to json parser and
      nlohmann::json jsonInput;
      std::ifstream jsonFile(inputFilename);
      jsonFile >> jsonInput;

      // Check if  "catalyst-scripts" exists and fill in
      if (jsonInput.find("catalyst-scripts") != jsonInput.end())
        for (int i=0; i<jsonInput["catalyst-scripts"].size(); i++)
        {
          std::string catalystFilepath = catalystPath +"/"+ std::string(jsonInput["catalyst-scripts"][i]);
          catalyst_scripts.push_back(catalystFilepath);

		  std::cout << "Catalyst script " << catalystFilepath << std::endl;
        }
    }
    else
      std::cout << "No input file detected for catalyst" << std::endl;
  
	return catalyst_scripts;
}