#pragma once

#include <vector>
#include <set>

class StringUtil
{
public:
	 static std::vector<std::string> Split(std::string str, std::string delimiter = "\n");
	 static std::string TrimWhitespace(std::string str);

	 static std::vector<std::vector<std::string>> MakeClusters(std::vector<std::string> data);
	 static std::vector<int> MakeIndices(std::string str);

	 static bool IsWhitespace(std::string str);
	 static void DiscardWhitespace(std::vector<std::string>& vec);

	 static size_t CountLines(const std::string& str);

	 static std::string StripFileExtension(std::string str);

private:
	static const std::set<char> whitespace;
};