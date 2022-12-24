#pragma once
#include <Windows.h>

class Clock
{
public:
	Clock();
	~Clock();
	double GetTime();
	void Reset();

private:
	double sysFre;		// 计时器频率
	double baseTime;	// 基础时间
};

