#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

#include "json.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

		      //std::cout << "Catalyst script " << catalystFilepath << std::endl;
        }
    }
    else
      std::cout << "No input file detected for catalyst" << std::endl;
  
	return catalyst_scripts;
}


inline std::string replaceInString(std::string original, std::string stringToReplace, std::string replacement)
{
  auto found = original.find(stringToReplace);
  original.replace(found, stringToReplace.length(), replacement);

  return original;
}


inline bool fileExists(const std::string& name) 
{
    std::ifstream f(name.c_str());
    if (f.good())
      std::cout << name << " exists" << std::endl;
    else
      std::cout << name << " does NOT exists" << std::endl;

    return (f.good());
}



inline bool imageCompare(std::string imageA, std::string imageB)
{
  int widthA, heightA, channelsA;
  unsigned char *imgA = stbi_load(imageA.c_str(), &widthA, &heightA, &channelsA, 0);
  if (imgA == NULL)
  {
    std::cout << "Could not load " << imageA << std::endl;
    return false;
  }

  int widthB, heightB, channelsB;
  unsigned char *imgB = stbi_load(imageB.c_str(), &widthB, &heightB, &channelsB, 0);
  if (imgB == NULL)
  {
    std::cout << "Could not load " << imageB << std::endl;
    return false;
  }

  if (widthA != widthB)
  {
    std::cout << "Image widths are different" << std::endl;
    return false;
  }

  if (heightA != heightB)
  {
    std::cout << "Image heights are different" << std::endl;
    return false;
  }

  if (channelsA != channelsB)
  {
    std::cout << "number of channels are different" << std::endl;
    return false;
  }
    

  size_t numPixels = widthA*heightA*channelsA;
  for (int i=0; i<numPixels; i++)
    if (imgA[i] != imgB[i])
    {
      std::cout << "pixels different!" << std::endl;
      return false;
    }

  std::cout << "Images " << imageA << " and " << imageB << " are identical!" << std::endl;

  // If all tests pass
  return true;
}



inline bool compareFiles(const std::string& p1, const std::string& p2) 
{
  std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
  std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

  if (f1.fail())
  {
    std::cout << "Could not read " << p1 << std::endl;
    return false;
  }

  if (f2.fail())
  {
    std::cout << "Could not read " << p2 << std::endl;
    return false;
  }

  if (f1.tellg() != f2.tellg()) 
  {
    std::cout << "Size mismatch for files " << p1 << " and " << p2 << " : " << f1.tellg() << " v/s " << f2.tellg() << std::endl;
    return false; //size mismatch
  }

  //seek back to beginning and use std::equal to compare contents
  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);
  bool match = std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f2.rdbuf()));
  
  if (match)
    std::cout << "Files " << p1 << " and " << p2 << " are identical!" << std::endl;
  
  return match;
}