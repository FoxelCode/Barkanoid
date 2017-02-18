#include "Log.hpp"

#include <iostream>

void Log::Print(std::string msg, std::string source, LogSeverity severity)
{
	std::cout << "[" << source << "]";
	if (severity == LogSeverity::Warning)
		std::cout << "[Warning] ";
	else if (severity == LogSeverity::Error)
		std::cout << "[Error]   ";
	std::cout << msg << std::endl;
}
