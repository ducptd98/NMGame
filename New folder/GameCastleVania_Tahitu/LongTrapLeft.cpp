#include "LongTrapLeft.h"

LongTrapLeft::LongTrapLeft()
{
	initTime();
}

LongTrapLeft::~LongTrapLeft()
{
}

void LongTrapLeft::initTime()
{
	gameTimeLoop.init(0.25, 6);
	gameTimeLoop.start();
	isReturn = false;
	height = 18;
	if (sprite != 0)
		sprite->animates[0].frames[0].y = 54;
}
