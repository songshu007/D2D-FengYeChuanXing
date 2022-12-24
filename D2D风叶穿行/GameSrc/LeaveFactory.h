#pragma once
#include "./Shamrock1.h"
#include "./Shamrock_trap.h"
#include "./Shamrock_lucky.h"
#include "./Shamrock2.h"
#include "./Shamrock3.h"
#include "./Shamrock4.h"

enum class LeaveType { Shamrock1, Shamrock2, Shamrock3, Shamrock4, Shamrock_trap, Shamrock_lucky };

class LeaveFactory
{
public:
	LeaveFactory();
	~LeaveFactory();

	Entity* GetLeave(LeaveType type);

};

