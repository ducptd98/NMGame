#include "Life.h"
#include "Map.h"

void Life::next(int& curFrame)
{
}

void Life::draw()
{
	DrawableObject::draw();
}

void Life::updateLocation()
{
	x = -Map::curMap->xMap + 50;
	y = -Map::curMap->yMap + 18;
}

Life::Life()
{
	sprite = SPRITEMANAGER->sprites[SPR_INFOMATION];
	direction = Left;
	curAnimation = 1;
	nextAnimation = 1;
	curFrame = LT_PLAYER;
	gameTimeLoop.init(0.2, 400);
	gameTimeLoop.start();
}

Life::~Life()
{
}
