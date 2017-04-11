#pragma once

#include <vector>
#include <set>

class StringUtil
{
public:
	 static std::vector<std::string> Split(std::string str, std::string delimiter = "\n");
	 /// <summary>
	 /// <para>Trims leading and trailing whitespace from a string.</para>
	 /// </summary>
	 static std::string TrimWhitespace(std::string str);

	 /// <summary>
	 /// <para>Splits a vector of lines into clusters.</para>
	 /// <para>Clusters are separated by an empty line.</para>
	 /// </summary>
	 /// <returns>Clusters extracted from the input lines.</returns>
	 static std::vector<std::vector<std::string>> MakeClusters(std::vector<std::string> data);

	 /// <summary>
	 /// <para>Splits a string into indices.</para>
	 /// <para>Indices are used for stage brick data, and are separated by spaces.</para>
	 /// </summary>
	 /// <returns>Indices extracted from the input string.</returns>
	 static std::vector<int> MakeIndices(std::string str);

	 static bool IsWhitespace(std::string str);
	 static void DiscardWhitespace(std::vector<std::string>& vec);

	 static std::string StripFileExtension(std::string str);

private:
	static const std::set<char> whitespace;
};