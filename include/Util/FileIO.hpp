#pragma once

class FileIO
{
public:
	static std::string ReadFile(const std::string& path);
	static void WriteFile(const std::string& path, const std::string& data);
};