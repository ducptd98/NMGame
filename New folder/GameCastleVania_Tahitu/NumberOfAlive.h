#pragma once
#include "Number.h"

class NumberOfAlive : public Number
{
public:
	Number* number;

	void draw();
	void update();

	NumberOfAlive();
	~NumberOfAlive();
};

