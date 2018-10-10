#include "Weapon.h"
#include "Simon.h"
#include "WeaponLocations.h"
#include "Stage.h"
#include "TileMap.h"

void Weapon::update()
{
	DrawableObject::update();
}

void Weapon::draw()
{
	DrawableObject::draw();
}

void Weapon::onAABBCheck(BaseObject * other)
{
}

Weapon::Weapon()
{
	direction = SIMON->direction;
	width = 16;
	height = 16;
	x = SIMON->x + WEAPONLOCATION->pts[2].x - width;
	y = SIMON->y + WEAPONLOCATION->pts[2].y - height / 3 * 2;
	x -= SIMON->updateX;
	if (direction == Right)
		x += 16 + width;
	dx = direction * 1.5;
	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 2;
	collisionType = CT_WEAPON;
	allowDelete = false;
}

Weapon::~Weapon()
{
}
