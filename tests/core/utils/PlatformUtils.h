#pragma once

#include <string>

class FileDialogs
{
public:
	// These return empty strings if cancelled
	static std::string OpenFile(const char* filter);
	static std::string SaveFile(const char* filter);
};

class Time
{
public:
	static float GetTime();
};