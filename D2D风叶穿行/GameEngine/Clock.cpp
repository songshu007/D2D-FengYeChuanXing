#include "Clock.h"
#include <iostream>

Clock::Clock()
	:sysFre(0.0f), baseTime(0.0f)
{
	LARGE_INTEGER temp_time;
	BOOL hr = QueryPerformanceFrequency(&temp_time);
	if (hr)
		sysFre = temp_time.QuadPart;	// 获取计时器频率

	memset(&temp_time, 0, sizeof(temp_time));

	hr = QueryPerformanceCounter(&temp_time);
	if (hr)
		baseTime = temp_time.QuadPart;	// 设置基础时间
}

Clock::~Clock()
{
}

double Clock::GetTime()
{
	double t = 0;
	LARGE_INTEGER temp_time;
	BOOL hr = QueryPerformanceCounter(&temp_time);
	if (hr)
	{
		return ((double)temp_time.QuadPart - baseTime) / sysFre;
	}
	else
	{
		return 0;
	}
}

void Clock::Reset()
{
	double t = 0;
	LARGE_INTEGER temp_time;
	BOOL hr = QueryPerformanceCounter(&temp_time);
	if (hr)
		baseTime = (double)temp_time.QuadPart;
}
