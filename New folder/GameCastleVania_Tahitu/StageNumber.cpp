#include "StageNumber.h"
#include "Simon.h"

void StageNumber::draw()
{
	for (int i = 0; i < 2; i++)
	{
		number[i].updateLocation();
		number[i].x += i * 8 + 90;
		number[i].draw();
	}
}

void StageNumber::update()
{
	number[1].curFrame = SIMON->stage;
}

StageNumber::StageNumber()
{
	number = new Number[2];
	number[1].curFrame = 4;
}

StageNumber::~StageNumber()
{
	delete[] number;
}
