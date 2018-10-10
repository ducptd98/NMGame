#include "NumberOfAlive.h"
#include "Simon.h"

void NumberOfAlive::draw()
{
	number[0].updateLocation();
	number[1].updateLocation();

	number[0].x += 47;
	number[1].x += 55;
	number[0].y += 25;
	number[1].y += 25;

	number[0].draw();
	number[1].draw();
}

void NumberOfAlive::update()
{
	if (number[0].gameTimeLoop.canCreateFrame())
	{
		number[1].curFrame = SIMON->numberOfAlive % 10;
		number[0].curFrame = (SIMON->numberOfAlive / 10) % 10;
	}

	if (number[0].gameTimeLoop.isTerminated())
		number[0].gameTimeLoop.start();
}

NumberOfAlive::NumberOfAlive()
{
	number = new Number[2];
	number[1].curFrame = 3;
	number[0].gameTimeLoop.init(0.2, 400);
	number[1].gameTimeLoop.init(0.2, 400);
}

NumberOfAlive::~NumberOfAlive()
{
	delete[] number;
}
