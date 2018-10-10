#include "Number.h"
#include "Map.h"

void Number::next(int& curFrame)
{
	curFrame--;

	if (curFrame == -1)
		curFrame = 9;
}

void Number::draw()
{
	DrawableObject::draw();
}

void Number::updateLocation()
{
	x = -Map::curMap->xMap + 145;
	y = -Map::curMap->yMap + 5;
}

Number::Number()
{
	sprite = SPRITEMANAGER->sprites[SPR_INFOMATION];
	direction = Left;
	curAnimation = 0;
	nextAnimation = 0;
	curFrame = 0;
	gameTimeLoop.init(1, 400);
	gameTimeLoop.start();
}

Number::~Number()
{
}
