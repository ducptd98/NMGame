#pragma once
#include "Number.h"

class Score
{
public:
	Number* number;

	void draw();
	void update();

	Score();
	~Score();
};

