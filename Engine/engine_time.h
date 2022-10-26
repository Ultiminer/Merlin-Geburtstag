#ifndef ENGINE_TIME_H_
#define ENGINE_TIME_H_
#include <chrono>
#include <ctime>
static std::chrono::high_resolution_clock::time_point ENGINE_START_TIME=std::chrono::high_resolution_clock::now(); 
inline double SysTime()noexcept
{
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> time_span = t2 - ENGINE_START_TIME;
	return time_span.count();
}
inline std::string CurrDate()noexcept
{
	auto start = std::chrono::system_clock::now();
	auto legacyStart = std::chrono::system_clock::to_time_t(start);
	char tmBuff[30];
	ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);
	return tmBuff;
}

#endif
