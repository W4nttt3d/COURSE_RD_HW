#include "DateTime.h"

#include <ctime>
#include <string>

int getDay(const std::tm* tmObj)
{
	return tmObj->tm_mday;
}

int getMonth(const std::tm* tmObj)
{
	return tmObj->tm_mon + 1;
}

int getYear(const std::tm* tmObj)
{
	return tmObj->tm_year + 1900;
}

std::string getDateTime()
{
	std::time_t t = std::time(nullptr);
	std::tm now;
	localtime_s(&now, &t);

	std::string dateTime = std::to_string(getDay(&now)) + "." + std::to_string(getMonth(&now)) + "." + std::to_string(getYear(&now));

	return dateTime;
}