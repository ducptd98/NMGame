#include "LongTrapRight.h"

void LongTrapRight::update()
{
	if (isStart)
	{
		if (timeStart.canCreateFrame())
		{
			sprite->animates[0].frames[0].y -= 9;
			height += 9;
		}

		if (timeStart.isTerminated())
			isStart = false;
	}
	else
		Trap::update();
}

void LongTrapRight::initTime()
{
	gameTimeLoop.init(0.25, 6);
	gameTimeLoop.start();
	sprite = SPRITEMANAGER->sprites[SPR_LONG_TRAP_RIGHT];
	sprite->animates[0].frames[0].y = 27;
	height = 45;
	isStart = true;
	timeStart.init(0.2, 3);
	timeStart.start();
	isReturn = true;
}

LongTrapRight::LongTrapRight()
{
	initTime();
}

LongTrapRight::~LongTrapRight()
{
}
