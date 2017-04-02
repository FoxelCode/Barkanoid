#include "Util/FileIO.hpp"

#include <fstream>

std::string FileIO::ReadFile(const std::string& path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.is_open())
	{
		LOG_ERROR("Couldn't open file: " + path);
		return "";
	}

	std::string output;
	std::string line;
	while (!inFile.eof())
	{
		std::getline(inFile, line);
		output += line + "\n";
	}
	output.pop_back();
	inFile.close();
	return output;
}
