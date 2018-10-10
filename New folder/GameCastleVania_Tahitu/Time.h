#pragma once
#include "Number.h"

class Time
{
public:
	Number* number;
	bool down;

	void draw();
	void update();

	Time();
	~Time();
};

