#pragma once

#include "Log.hpp"

#define LOG_WARNING(msg) Log::Print(msg, __FUNCTION__, LogSeverity::Warning);
#define LOG_ERROR(msg) Log::Print(msg, __FUNCTION__, LogSeverity::Error);