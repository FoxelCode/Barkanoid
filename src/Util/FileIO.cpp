#include "Util/FileIO.hpp"

#include <fstream>

std::string FileIO::ReadFile(const std::string& path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.is_open())
	{
		LOG_ERROR("Couldn't open file: " + path + " for reading");
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

void FileIO::WriteFile(const std::string& path, const std::string& data)
{
	std::ofstream outFile;
	outFile.open(path);
	if (!outFile.is_open())
	{
		LOG_ERROR("Couldn't open file: " + path + " for writing");
		return;
	}

	outFile << data;
	outFile.close();
}
