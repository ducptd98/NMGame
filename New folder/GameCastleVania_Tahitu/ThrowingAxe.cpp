#include "ThrowingAxe.h"

List<ThrowingAxe*>* ThrowingAxe::throwingAxes = 0;
List<ThrowingAxe*>* ThrowingAxe::getThrowingAxes()
{
	if (throwingAxes == 0)
		throwingAxes = new List<ThrowingAxe*>();
	return throwingAxes;
}

void ThrowingAxe::updateVerlocity()
{
	vy += ay * TIME;
	dx = vx * TIME;
	dy = vy * TIME;
}

void ThrowingAxe::update()
{
	isCollisionCross = false;
	isCollision = false;

	updateVerlocity();
}

void ThrowingAxe::draw()
{
	Weapon::draw();
}

void ThrowingAxe::onAABBCheck(BaseObject * other)
{
	Weapon::onAABBCheck(other);
}

ThrowingAxe::ThrowingAxe()
{
	sprite = SPRITEMANAGER->sprites[SPR_THROWING_AXE];
	getThrowingAxes()->_Add(this);
	vy = -180;
	vx = direction * 40;
	ay = GRAVITY;
}

ThrowingAxe::~ThrowingAxe()
{
}
