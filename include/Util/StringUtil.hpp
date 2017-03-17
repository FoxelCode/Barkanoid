#pragma once

#include <vector>

class StringUtil
{
public:
	 static std::vector<std::string> Split(std::string str, std::string delimiter = "\n");
};