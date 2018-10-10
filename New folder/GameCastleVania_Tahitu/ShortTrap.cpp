#include "ShortTrap.h"

ShortTrap::ShortTrap()
{
	initTime();
}

ShortTrap::~ShortTrap()
{
}

void ShortTrap::initTime()
{
	gameTimeLoop.init(0.25, 4);
	gameTimeLoop.start();
	isReturn = false;
	height = 18;
	if (sprite != 0)
		sprite->animates[0].frames[0].y = 54;
}
