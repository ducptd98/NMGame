#include "NumberOfAttack.h"
#include "Simon.h"

void NumberOfAttack::draw()
{
	number[0].updateLocation();
	number[1].updateLocation();

	number[0].x += 47;
	number[1].x += 55;
	number[0].y += 13;
	number[1].y += 13;

	number[0].draw();
	number[1].draw();
}

void NumberOfAttack::update()
{
	if (number[0].gameTimeLoop.canCreateFrame())
	{
		number[1].curFrame = SIMON->numberOfAttacks % 10;
		number[0].curFrame = (SIMON->numberOfAttacks / 10) % 10;
	}

	if (number[0].gameTimeLoop.isTerminated())
		number[0].gameTimeLoop.start();
}

NumberOfAttack::NumberOfAttack()
{
	number = new Number[2];
	number[1].curFrame = 5;
	number[0].gameTimeLoop.init(0.2, 400);
	number[1].gameTimeLoop.init(0.2, 400);
}

NumberOfAttack::~NumberOfAttack()
{
	delete[] number;
}
