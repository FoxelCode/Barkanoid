#include "Log.hpp"

#include <iostream>

void Log::Print(std::string msg, std::string source, LogSeverity severity)
{
	if (severity == LogSeverity::Warning)
		std::cout << "[Warn]";
	else if (severity == LogSeverity::Error)
		std::cout << "[Err]";
	std::cout << "[" << source << "]: " << msg << std::endl;
}
