#include "WeaponType.h"
#include "Map.h"
#include "Simon.h"

void WeaponType::draw()
{
	updateLocation();
	DrawableObject::draw();
}

void WeaponType::update()
{
	if (SIMON->weaponType == WT_DEFAULT)
		curFrame = IT_DEFAULT;

	if (SIMON->weaponType == WT_BOOMERANG)
		curFrame = IT_BOOMERANG;

	if (SIMON->weaponType == WT_DAGGER)
		curFrame = IT_DAGGER;

	if (SIMON->weaponType == WT_HOLY_WATER)
		curFrame = IT_HOLY_WATER;

	if (SIMON->weaponType == WT_STOPWATCH)
		curFrame = IT_STOP_WATCH;

	if (SIMON->weaponType == WT_THROWING_AXE)
		curFrame = IT_THROWING_AXE;
}

void WeaponType::updateLocation()
{
	x = -Map::curMap->xMap + 137;
	y = -Map::curMap->yMap + 18;
}

WeaponType::WeaponType()
{
	sprite = SPRITEMANAGER->sprites[SPR_INFOMATION];
	direction = Left;
	curAnimation = 2;
	nextAnimation = 2;
	curFrame = IT_DEFAULT;
	gameTimeLoop.init(0.2, 400);
	gameTimeLoop.start();
}

WeaponType::~WeaponType()
{
}
