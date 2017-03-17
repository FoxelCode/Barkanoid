#include "Util/StringUtil.hpp"

std::vector<std::string> StringUtil::Split(std::string str, std::string delimiter)
{
	std::vector<std::string> output;
	size_t pos = 0;
	while ((pos = str.find(delimiter)) != std::string::npos)
	{
		// Get the line up to the delimiter and erase it from the string
		output.push_back(str.substr(0, pos));
		str.erase(0, pos + 1);
	}
	// Also add the last remaining line
	output.push_back(str);
	return output;
}
