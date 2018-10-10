#pragma once
#include "Trap.h"

class LongTrapRight : public Trap
{
public:
	bool isStart;
	GameTimeLoop timeStart;

	void update();

	void initTime();

	LongTrapRight();
	~LongTrapRight();
};

