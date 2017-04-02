#pragma once

#include <string>

enum LogSeverity
{
	Info,
	Warning,
	Error
};

class Log
{
public:
	static void Print(std::string msg, std::string source = "", LogSeverity severity = LogSeverity::Error);
};