#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string LoadFileAsString(std::string filename)
{
	std::stringstream fileNow;
	std::ifstream file(filename);

	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			fileNow << line << std::endl;
		}
		return fileNow.str();
	}
	else
	{
		std::cout << "Error loading file: " << filename << std::endl;
		return "";
	}
}
