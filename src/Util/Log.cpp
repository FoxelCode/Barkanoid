#include "Util/Log.hpp"

#include <iostream>

void Log::Print(std::string msg, std::string source, LogSeverity severity)
{
	std::cout << "[" << source << "]";
	switch (severity)
	{
	case Info:		std::cout << "[Info]    ";		break;
	case Warning:	std::cout << "[Warning] ";		break;
	case Error:		std::cout << "[Error]   ";		break;
	}
	std::cout << msg << std::endl;
}
