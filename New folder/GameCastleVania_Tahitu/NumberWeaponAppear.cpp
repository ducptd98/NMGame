#include "NumberWeaponAppear.h"
#include "Map.h"
#include "Simon.h"

void NumberWeaponAppear::draw()
{
	updateLocation();
	DrawableObject::draw();
}

void NumberWeaponAppear::update()
{
	if (SIMON->numberAppear == 1)
		curFrame = NT_DEFAULT;

	if (SIMON->numberAppear == 2)
		curFrame = NT_DOUBLESHOT;

	if (SIMON->numberAppear == 3)
		curFrame = NT_TRIPLESHOT;
}

void NumberWeaponAppear::updateLocation()
{
	x = -Map::curMap->xMap + 220;
	y = -Map::curMap->yMap + 18;
}

NumberWeaponAppear::NumberWeaponAppear()
{
	sprite = SPRITEMANAGER->sprites[SPR_INFOMATION];
	direction = Left;
	curAnimation = 3;
	nextAnimation = 3;
	curFrame = NT_DEFAULT;
	gameTimeLoop.init(0.2, 400);
	gameTimeLoop.start();
}

NumberWeaponAppear::~NumberWeaponAppear()
{
}
