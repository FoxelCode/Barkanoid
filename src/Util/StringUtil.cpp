#include "Util/StringUtil.hpp"

#include <string>

const std::set<char> StringUtil::whitespace = { ' ', '\t', '\0', '\r', '\n' };

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
	// Also add the last remaining part
	output.push_back(str);
	return output;
}

std::vector<std::vector<std::string>> StringUtil::MakeClusters(std::vector<std::string> data)
{
	std::vector<std::vector<std::string>> clusters;
	clusters.push_back(std::vector<std::string>());

	for (std::string line : data)
	{
		if (StringUtil::IsWhitespace(line))
			clusters.push_back(std::vector<std::string>());
		else
			clusters[clusters.size() - 1].push_back(line);
	}

	return clusters;
}

std::vector<int> StringUtil::MakeIndices(std::string str)
{
	std::vector<int> indices;
	// Split the string into parts divided by spaces
	std::vector<std::string> parts = Split(str, " ");
	// Discard parts that are just whitespace
	DiscardWhitespace(parts);

	for (std::string part : parts)
	{
		int val = -1;
		// Try to cast the part into an integer
		try
		{
			val = std::stoi(part);
			indices.push_back(val);
		}
		// If the casting failed, it's probably a character
		catch (std::invalid_argument i)
		{
			if (part.length() == 1)
				indices.push_back((int)part[0]);
		}
	}
	return indices;
}

bool StringUtil::IsWhitespace(std::string str)
{
	for (char& c : str)
		if (whitespace.find(c) == whitespace.end())
			return false;
	return true;
}

void StringUtil::DiscardWhitespace(std::vector<std::string>& vec)
{
	for (auto it = vec.begin(); it != vec.end(); )
	{
		bool isWhitespace = true;
		// Empty strings count as whitespace
		if ((*it).empty())
			isWhitespace = true;
		else
		{
			for (char c : (*it))
			{
				// If one of the characters in the string isn't whitespace, we can keep that string
				if (whitespace.find(c) == whitespace.end())
				{
					isWhitespace = false;
					break;
				}
			}
		}
		// Remove line if it consists only of whitespace
		if (isWhitespace)
		{
			it = vec.erase(it);
			continue;
		}
		it++;
	}
}

std::string StringUtil::StripFileExtension(std::string str)
{
	size_t dotIndex = -1;
	for (auto it = str.rbegin(); it != str.rend(); it++)
	{
		if ((*it) == '.')
		{
			dotIndex = str.size() - std::distance(str.rbegin(), it);
			break;
		}
	}
	if (dotIndex != -1)
		return str.substr(0, dotIndex - 1);
	return str;
}
