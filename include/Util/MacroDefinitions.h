#pragma once

#include "Log.hpp"

#define ASSERT(cond) if (!(cond)) { LOG_ERROR("Assertion failed"); abort(); }

#define LOG_INFO(msg)		Log::Print(msg, __FUNCTION__, LogSeverity::Info);
#define LOG_WARNING(msg)	Log::Print(msg, __FUNCTION__, LogSeverity::Warning);
#define LOG_ERROR(msg)		Log::Print(msg, __FUNCTION__, LogSeverity::Error);